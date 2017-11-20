/**************       Bplustree.c      *****************/
/*  To Compile      gcc -o  Bplustree  Bplustree.c     */  
/*  To Run          Bplustree  <input                  */
/*******************************************************/
 
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#ifndef _BTREE_

#ifdef __cplusplus
extern "C" {
#endif

int OpenIndex(char *Name, int DupKeys);
/* open or create index file, find free entry in index table,
    fill in entry, DupKeys is 1 if duplicate keys are allowed, 0 if not,
    return number of entry in table */

void CloseIndex(int Index);
/* close Index file, free entry in index info table */

int Insert(int Index, long Key, long Ptr);
/* insert Key & Ptr in index file, return 0 for success, nonzero for error */

long Lookup(int Index, long Key);
/* return pointer for entry in Index file <= Key, return -1 if none */


#ifdef __cplusplus
}
#endif

#endif

#define ORDER 64   
#define BLKSIZE (ORDER*8)
#define BKTPTRS (ORDER*2 - 1)
#define NLEN 40
#define NIDX 20
#define SEEK_SET  0   

typedef struct {
	short LeafNode;
	short KeyCount;
	long Keys[ORDER - 1];
	long Ptrs[ORDER];
} NodeType;

typedef struct {
	long RootBlock;
	long AllocBlock;
	char Junk[BLKSIZE - 2*sizeof(long)];
} HeadType;

typedef struct {
	long Pointers[BKTPTRS];
	long NextBucket;
} BucketType;

typedef struct {
	int Used;
	int File;
	char Name[NLEN];
	int DupKeys;
	long RootBlk;
	long AllocBlk;
	long CurBlk;
	short CurKey;
	short CurPtr;
} IdxInfo;
#define File(Idx)	(IdxTab[Idx].File)
#define Root(Idx)	(IdxTab[Idx].RootBlk)
#define Used(Idx)	(IdxTab[Idx].Used)
#define Dups(Idx)	(IdxTab[Idx].DupKeys)
#define Alloc(Idx)	(IdxTab[Idx].AllocBlk)
#define CBlk(Idx)	(IdxTab[Idx].CurBlk)
#define CKey(Idx)	(IdxTab[Idx].CurKey)
#define CPtr(Idx)	(IdxTab[Idx].CurPtr)

BucketType Bucket;  

static IdxInfo IdxTab[NIDX];

static void ReadBlock(int File, long Block, int Size, void *Addr) {
/*    
printf("ReadBlock(File %d, Block %ld, Size %d, Addr %x)\n",
File, Block, Size, Addr);
*/  

	if(lseek(File, Block * Size, SEEK_SET) == -1 ||
	   read(File, Addr, Size) == -1)
		printf("ReadBlock Error, File %d, Block %d, Size %d\n",
			File, Block, Size);
}

static void WriteBlock(int File, long Block, int Size, void *Addr) {
/* 
printf("WriteBlock(File %d, Block %ld, Size %d, Addr %x)\n",
File, Block, Size, Addr);
*/ 
	if(lseek(File, Block * Size, SEEK_SET) == -1 ||
	   write(File, Addr, Size) == -1)
		printf("WriteBlock Error, File %d, Block %d, Size %d\n",
			File, Block, Size);
}

static void ReadHead(int Index) {
	HeadType HeadBlock;
	ReadBlock(File(Index), 0, BLKSIZE, &HeadBlock);
	Root(Index) = HeadBlock.RootBlock;
	Alloc(Index) = HeadBlock.AllocBlock;
}

static void WriteHead(int Index) {
	HeadType HeadBlock;
        int i;
	HeadBlock.RootBlock = Root(Index);
	HeadBlock.AllocBlock = Alloc(Index);
	WriteBlock(File(Index), 0, BLKSIZE, &HeadBlock);
}

int OpenIndex(char *Name, int DupKeys) {
	int i;
	int j;
	for(i = 0; i < NIDX; i++)
		if(!Used(i)) break;
	Used(i) = 1;
	strcpy(IdxTab[i].Name, Name);
	Dups(i) = DupKeys;
	CBlk(i) = -1;
	if((File(i) = open(Name, O_RDWR)) >= 0) {
		ReadHead(i);
	} else
/*	if((File(i) = creat(Name, S_IREAD|S_IWRITE)) >= 0) {    */ 
        if((File(i) = open(Name, O_RDWR|O_CREAT, 0644)) >= 0) { 
		NodeType Node;
		Root(i) = 1;
		Alloc(i) = 2;
		WriteHead(i);
		Node.LeafNode = 1;
		Node.KeyCount = 0;
	        for(j = 0; j < ORDER-1; j++)
                  { 
                    Node.Ptrs[j] = -1; 
                    Node.Keys[j] = 0; 
                   }  
		Node.Ptrs[ORDER - 1] = -1;
		WriteBlock(File(i), 1, BLKSIZE, &Node);
	} else {
		perror("OpenIndex");
		Used(i) = 0;
		i = -1;
	}
	return i;
}

void CloseIndex(int Index) {
	WriteHead(Index);
	close(File(Index));
	Used(Index) = 0;
}

static int FindKey(NodeType *Node, long Key) {
	int k;
	for(k = 0; k < Node->KeyCount; k++)
		if(Node->Keys[k] > Key) break;
	return k;
}

static void CheckBucket(int Index, NodeType *Node, long *Key, long *Ptr) {
	*Ptr = -1;
	if(CBlk(Index) >= 0) {
		long NextPtr;
	*Key = Node->Keys[CKey(Index)-1];
	*Ptr = Node->Ptrs[CKey(Index)];
	if(Dups(Index)) {
/*		BucketType Bucket;   */ 
		ReadBlock(File(Index), *Ptr, BLKSIZE, &Bucket);
		*Ptr = Bucket.Pointers[CPtr(Index)];
		CPtr(Index)++;
		NextPtr = Bucket.Pointers[CPtr(Index)];
	}
	if(!Dups(Index) || NextPtr < 0) {
		CPtr(Index) = 0;
		CKey(Index)++;
		if(CKey(Index) > Node->KeyCount) {
			CBlk(Index) = Node->Ptrs[0];
			CKey(Index) = 1;
		}
	}
/*     
printf("I%d K%ld P%ld\n", Index, *Key, *Ptr);
*/  
	}
}

long Lookup(int Index, long Key) {
	NodeType Node;
	long Ptr;
	CBlk(Index) = Root(Index);
	for(;;) {
		ReadBlock(File(Index), CBlk(Index), BLKSIZE, &Node);
		CKey(Index) = FindKey(&Node, Key);
		if(Node.LeafNode) break;
		CBlk(Index) = Node.Ptrs[CKey(Index)];
	}
	CPtr(Index) = 0;
	if(CKey(Index) == 0) CBlk(Index) = -1;
	CheckBucket(Index, &Node, &Key, &Ptr);
	return Ptr;
}



static int InsertKey(int Index, NodeType *Node, int KIdx, long *Key, long *Ptr) {
	long Keys[ORDER], Ptrs[ORDER+1];
	int Count, Count1, Count2, k;
	Count = Node->KeyCount + 1;
	Count1 = Count < ORDER ? Count : ORDER/2;
	Count2 = Count - Count1;
	for(k = ORDER/2; k < KIdx; k++) {
		Keys[k] = Node->Keys[k];
		Ptrs[k+1] = Node->Ptrs[k+1];
	}
	Keys[KIdx] = *Key;
	Ptrs[KIdx+1] = *Ptr;
	for(k = KIdx; k < Node->KeyCount; k++) {
		Keys[k+1] = Node->Keys[k];
		Ptrs[k+2] = Node->Ptrs[k+1];
	}
	for(k = KIdx; k < Count1; k++) {
		Node->Keys[k] = Keys[k];
		Node->Ptrs[k+1] = Ptrs[k+1];
	}
	Node->KeyCount = Count1;
	if(Count2) {
		int s, d;
		NodeType NNode;
		NNode.LeafNode = Node->LeafNode;
		Count2 -= !Node->LeafNode;
		for(s = ORDER/2 + !Node->LeafNode, d = 0; d < Count2; s++, d++) {
			NNode.Keys[d] = Keys[s];
			NNode.Ptrs[d] = Ptrs[s];
		}
		NNode.Ptrs[d] = Ptrs[s];
		NNode.KeyCount = Count2;
		*Key = Keys[ORDER/2];
		*Ptr = Alloc(Index)++;
		if(Node->LeafNode) {  /* insert in sequential linked list */
			NNode.Ptrs[0] = Node->Ptrs[0];
			Node->Ptrs[0] = *Ptr;
		}
		WriteBlock(File(Index), *Ptr, BLKSIZE, &NNode);
		WriteHead(Index);
	}
	return Count2;
}

static long NewBucket(int Index, long Ptr, long Next) {
	long BBlk;
        int j; 
	BucketType Bucket;
	Bucket.Pointers[0] = Ptr;
        Bucket.Pointers[1] = -1;  
	Bucket.NextBucket = Next;
	BBlk = Alloc(Index)++;
	WriteBlock(File(Index), BBlk, BLKSIZE, &Bucket);
	WriteHead(Index);
	return BBlk;
}

static int Error;

static int RecInsert(int Index, long Block, long *Key, long *Ptr) {
	NodeType Node;
	int KIdx, Split = 0;
	int EqualKey;
	ReadBlock(File(Index), Block, BLKSIZE, &Node);
	KIdx = FindKey(&Node, *Key);
	EqualKey = KIdx && Node.Keys[KIdx-1] == *Key;
	if(!Node.LeafNode)
		Split = RecInsert(Index, Node.Ptrs[KIdx], Key, Ptr);
	if(Split || Node.LeafNode && !EqualKey) {
		if(Node.LeafNode && Dups(Index))
			*Ptr = NewBucket(Index, *Ptr, -1);
		Split = InsertKey(Index, &Node, KIdx, Key, Ptr);
		WriteBlock(File(Index), Block, BLKSIZE, &Node);
	} else if(Node.LeafNode && Dups(Index)) { /* put in existing bucket */
		BucketType Bucket;
		int i;
		ReadBlock(File(Index), Node.Ptrs[KIdx], BLKSIZE, &Bucket);
		for(i = 0; i < BKTPTRS && Bucket.Pointers[i] >= 0; i++);
		if(i < BKTPTRS) {
		    Bucket.Pointers[i] = *Ptr;
		    if(i < BKTPTRS-1) Bucket.Pointers[i+1] = -1;
		    WriteBlock(File(Index), Node.Ptrs[KIdx], BLKSIZE, &Bucket);
		} else {
			printf("ERROR: Bucket Overflow\n");
		}
	} else if(Node.LeafNode) {
		Error = -1;
	}
	return Split;
}

int Insert(int Index, long Key, long Ptr) {
	int Split;
	Error = 0;
	Split = RecInsert(Index, Root(Index), &Key, &Ptr);
	if(Split) {
		NodeType Node;
		Node.LeafNode = 0;
		Node.KeyCount = 1;
		Node.Keys[0] = Key;
		Node.Ptrs[1] = Ptr;
		Node.Ptrs[0] = Root(Index);
		Root(Index) = Alloc(Index)++;
		WriteBlock(File(Index), Root(Index), BLKSIZE, &Node);
		WriteHead(Index);
	}
	CBlk(Index) = -1;
	return Error;
}

main()  {

/********************************************************************/
/* The main section of code should be replaced.                     */ 
/* It just illustrates how keys and addresses can be inserted       */   
/* into a B+ tree and then retrieved                                */   
/********************************************************************/

 char Xname[8];
  int  Xdupkeys; 
  int  XEntryNum; 
  long XKey, XPtr;    
  int  RetnCode;     
  int  i,j;     

  int NumInsert, NumLookup;  

  printf("start main\n");  

  Xdupkeys  = 0;  
  Xname[0]  = 'm'; 
  Xname[1]  = 'y'; 
  Xname[2]  = 'f'; 
  Xname[3]  = 'i'; 
  Xname[4]  = 'l'; 
  Xname[5]  = 'e'; 
  

/********************************************************************/  
/* read number of keys to insert, the number of keys  to search for */ 
/* and whether duplicates are allowed in the index                  */ 
/********************************************************************/  

  scanf("%d  %d  %d",&NumInsert, &NumLookup, &Xdupkeys);

  XEntryNum = OpenIndex(Xname, Xdupkeys);  

  for(i = 0; i < NumInsert; i++){  
		printf("Insert KEY, PTR:");
/* read key and address  to insert into the B+ tree  */ 

       scanf("%d  %d",&XKey, &XPtr);
       printf("%d  %d",XKey, XPtr);
       printf("\n");

       RetnCode = Insert(XEntryNum, XKey, XPtr);        
       if (RetnCode != 0)  
          printf("Error During Key Insertion\n");         
     }  


 for(i = 0; i < NumLookup; i++)
     {  

/* read key to lookup in the B+ tree  */ 
		printf("Search KEY:");
       scanf("%d",&XKey);
       printf("%d",XKey);
       printf("\n");
       XPtr = Lookup(XEntryNum, XKey);   
       if (Xdupkeys == 0)  {  
         printf("Key value is %d and Ptr value is %d\n", XKey, XPtr);    
        } 
       else 
         printf("Key value is %d\n", XKey);  

       if (Xdupkeys == 1) { 
         j = 0;  
         while (Bucket.Pointers[j] != -1)  { 
            printf("Ptr value is %d\n", Bucket.Pointers[j]); 
            j++; 
           } 
       }    
     }  


  CloseIndex(XEntryNum);

  printf("finish main\n");  


}
