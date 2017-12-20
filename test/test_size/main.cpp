#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BPT_KEY_TYPE long
#define BPT_VALUE_TYPE long
#define BPT_MAX_LEVEL 32
#define BPT_MAX_ORDER 30
#define BPT_MIN_ORDER 8
#define BPT_MAX_ENTRIES 30
#define BPT_MIN_ENTRIES 8

const static int BPT_KEY_LEN 		= sizeof(uint64_t);
const static int BPT_VALUE_LEN 	= 8;
const static int BPT_KV_LEN 		= BPT_KEY_LEN + BPT_VALUE_LEN;
const static int BPT_ITER               = 100000;
const static int BPT_PRINT_ITER = 10000;

/* operation definitions */
const static int BPT_FIND		= 1;
const static int BPT_INSERT		= 2;
const static int BPT_DELETE		= 3;


enum{
	BPLUS_TREE_NON_LEAF,
	BPLUS_TREE_LEAF = 1
};
struct bplus_node {
	long lock;
	long type;
	struct bplus_non_leaf *parent;
};

struct bplus_non_leaf {
	long lock;
	long type;
	struct bplus_non_leaf *parent;
	struct bplus_non_leaf *next;
	long children;
	BPT_KEY_TYPE key[BPT_MAX_ORDER - 1];
	struct bplus_node *sub_ptr[BPT_MAX_ORDER];
};

struct bplus_leaf {
	long type;
	struct bplus_non_leaf *parent;
	struct bplus_leaf *next;
	long entries;
	BPT_KEY_TYPE key[BPT_MAX_ENTRIES];
	BPT_VALUE_TYPE data[BPT_MAX_ENTRIES];
};

struct bplus_tree {
	long order;
	long entries;
	long level;
	struct bplus_node *root;
	struct bplus_node *head[BPT_MAX_LEVEL];
};

int main() {
	printf("%d\n", sizeof(struct bplus_non_leaf));
	printf("%d\n", sizeof(struct bplus_leaf));
	return 0;
}
