#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define KEY_TYPE long
#define VALUE_TYPE long
#define MAX_LEVEL 32
#define MAX_ORDER 32
#define MIN_ORDER 8
#define MAX_ENTRIES 32
#define MIN_ENTRIES 8
#define TM_STORE(x, y) { *((long *)x) = (long)y; }
#define TM_LOAD(x) *(x)
#define TM_MALLOC malloc
#define PMALLOC malloc

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
        KEY_TYPE key[MAX_ORDER - 1];
        struct bplus_node *sub_ptr[MAX_ORDER];
};

struct bplus_leaf {
        long lock;
        long type;
        struct bplus_non_leaf *parent;
        struct bplus_leaf *next;
        long entries;
        KEY_TYPE key[MAX_ENTRIES];
        VALUE_TYPE data[MAX_ENTRIES];
};

struct bplus_tree {
        long order;
        long entries;
        long level;
        struct bplus_node *root;
        struct bplus_node *head[MAX_LEVEL];
};

static long
key_binary_search(long *arr, long len, long target)
{
    long low = -1;
    long high = len;
    while (low + 1 < high) {
        long mid = low + (high - low) / 2;
        if (target > TM_LOAD(&arr[mid])) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high >= len || TM_LOAD(&arr[high]) != target) {
        return -high - 1;
    } else {
        return high;
    }
}

static struct bplus_non_leaf *
non_leaf_new(void)
{
    struct bplus_non_leaf *node = (struct bplus_non_leaf*)TM_MALLOC(sizeof(struct bplus_non_leaf));
    assert(node != NULL);
    TM_STORE(&node->type, BPLUS_TREE_NON_LEAF);
    TM_STORE(&node->parent, NULL);
    TM_STORE(&node->next, NULL);
    return node;
}

static struct bplus_leaf *
leaf_new(void)
{
    struct bplus_leaf *node = (struct bplus_leaf*)TM_MALLOC(sizeof(struct bplus_leaf));
    assert(node != NULL);
    TM_STORE(&node->type, BPLUS_TREE_LEAF);
    TM_STORE(&node->parent, NULL);
    TM_STORE(&node->next, NULL);
    return node;
}


static VALUE_TYPE
bplus_tree_search(struct bplus_tree *tree, long key)
{
    long i;
    struct bplus_node *node = (struct bplus_node *)TM_LOAD(&tree->root);
    struct bplus_non_leaf *nln;
    struct bplus_leaf *ln;

    while (node != NULL) {
        switch (TM_LOAD(&node->type)) {
            case BPLUS_TREE_NON_LEAF:
                nln = (struct bplus_non_leaf *)node;
                i = key_binary_search(nln->key, TM_LOAD(&nln->children) - 1, key);
                if (i >= 0) {
                    node = (struct bplus_node *)TM_LOAD(&nln->sub_ptr[i + 1]);
                } else {
                    i = -i - 1;
                    node = (struct bplus_node *)TM_LOAD(&nln->sub_ptr[i]);
                }
                break;
            case BPLUS_TREE_LEAF:
                ln = (struct bplus_leaf *)node;
                i = key_binary_search(ln->key, (long)TM_LOAD(&ln->entries), key);
                if (i >= 0) {
                    return (VALUE_TYPE)TM_LOAD(&ln->data[i]);
                } else {
                    return 0;
                }
            default:
                assert(0);
        }
    }

    return 0;
}

static long
non_leaf_insert(struct bplus_tree *tree, struct bplus_non_leaf *node, struct bplus_node *sub_node, long key, long level)
{
    long i, j, split_key;
    long split = 0;
    struct bplus_non_leaf *sibling;

    long insert = key_binary_search(node->key, TM_LOAD(&node->children) - 1, key);
    assert(insert < 0);
    insert = -insert - 1;

    int order = TM_LOAD(&tree->order);
    /* node full */
    if (TM_LOAD(&node->children) == order) {
        /* split = [m/2] */
        split = (order + 1) / 2;
        /* splited sibling node */
        sibling = non_leaf_new();
        TM_STORE(&sibling->next, (struct bplus_non_leaf*)TM_LOAD(&node->next));

        TM_STORE(&node->next, sibling);
        /* non-leaf node's children always equals to split + 1 after insertion */
        TM_STORE(&node->children, split + 1);
        /* sibling node replication due to location of insertion */
        if (insert < split) {
            split_key = TM_LOAD(&node->key[split - 1]);
            /* sibling node's first sub-node */
            struct bplus_node* sub_ptr = (struct bplus_node*)TM_LOAD(&node->sub_ptr[split]);
            TM_STORE(&sibling->sub_ptr[0], sub_ptr);
            TM_STORE(&sub_ptr->parent, sibling);
            /* insertion point is before split point, replicate from key[split] */
            for (i = split, j = 0; i < order - 1; i++, j++) {
                struct bplus_node* sub_ptr = (struct bplus_node*)TM_LOAD(&node->sub_ptr[i+1]);

                TM_STORE(&sibling->key[j], TM_LOAD(&node->key[i]));
                TM_STORE(&sibling->sub_ptr[j + 1], sub_ptr);
                TM_STORE(&sub_ptr->parent, sibling);
            }
            TM_STORE(&sibling->children, j + 1);
            /* insert new key and sub-node */
            for (i = TM_LOAD(&node->children) - 2; i > insert; i--) {
                TM_STORE(&node->key[i], TM_LOAD(&node->key[i - 1]));
                TM_STORE(&node->sub_ptr[i + 1], TM_LOAD(&node->sub_ptr[i]));
            }
            TM_STORE(&node->key[i], key);
            TM_STORE(&node->sub_ptr[i + 1], sub_node);
            TM_STORE(&sub_node->parent, node);
        } else if (insert == split) {
            split_key = key;
            /* sibling node's first sub-node */
            TM_STORE(&sibling->sub_ptr[0], sub_node);
            TM_STORE(&sub_node->parent, sibling);
            /* insertion point is split point, replicate from key[split] */
            for (i = split, j = 0; i < order - 1; i++, j++) {
                struct bplus_node* sub_ptr = (struct bplus_node*)TM_LOAD(&node->sub_ptr[i+1]);

                TM_STORE(&sibling->key[j], TM_LOAD(&node->key[i]));
                TM_STORE(&sibling->sub_ptr[j + 1], sub_ptr);
                TM_STORE(&sub_ptr->parent, sibling);
            }
            TM_STORE(&sibling->children, j + 1);
        } else {
            split_key = TM_LOAD(&node->key[split]);
            /* sibling node's first sub-node */
            struct bplus_node* sub_ptr = (struct bplus_node*)TM_LOAD(&node->sub_ptr[split + 1]);
            TM_STORE(&sibling->sub_ptr[0], sub_ptr);
            TM_STORE(&sub_ptr->parent, sibling);
            /* insertion point is after split point, replicate from key[split + 1] */
            for (i = split + 1, j = 0; i < order - 1; j++) {
                if (j != insert - split - 1) {
                    struct bplus_node* sub_ptr = (struct bplus_node*)TM_LOAD(&node->sub_ptr[i+1]);

                    TM_STORE(&sibling->key[j], TM_LOAD(&node->key[i]));
                    TM_STORE(&sibling->sub_ptr[j + 1], sub_ptr);
                    TM_STORE(&sub_ptr->parent, sibling);
                    i++;
                }
            }
            /* reserve a hole for insertion */
            if (j > insert - split - 1) {
                TM_STORE(&sibling->children, j + 1);
            } else {
                assert(j == insert - split - 1);
                TM_STORE(&sibling->children, j + 2);
            }
            /* insert new key and sub-node*/
            j = insert - split - 1;
            TM_STORE(&sibling->key[j], key);
            TM_STORE(&sibling->sub_ptr[j + 1], sub_node);
            TM_STORE(&sub_node->parent, sibling);
         }
    } else {
        /* simple insertion */
        long children =  TM_LOAD(&node->children);
        for (i = children- 1; i > insert; i--) {
            TM_STORE(&node->key[i], TM_LOAD(&node->key[i - 1]));
            TM_STORE(&node->sub_ptr[i + 1], TM_LOAD(&node->sub_ptr[i]));
        }
        

        TM_STORE(&node->key[i], key);
        TM_STORE(&node->sub_ptr[i + 1], sub_node);
        TM_STORE(&node->children, children+1);
    }

    if (split) {
        struct bplus_non_leaf *parent = (struct bplus_non_leaf*)TM_LOAD(&node->parent);
        if (parent == NULL) {
            if (++level >= TM_LOAD(&tree->level)) {
                fprintf(stderr, "!!Panic: Level exceeded, please expand the tree level, non-leaf order or leaf entries for element capacity!\n");
                assert(0);
                //exit(-1);
                //TM_STORE(&node->next, sibling->next);
                //return -1;
            }
            /* new parent */
            parent = non_leaf_new();
            TM_STORE(&parent->key[0], split_key);
            TM_STORE(&parent->sub_ptr[0], node);
            TM_STORE(&parent->sub_ptr[1], sibling);
            TM_STORE(&parent->children, 2);
            /* update root */
            TM_STORE(&tree->root, parent);
            TM_STORE(&tree->head[level], parent);
            TM_STORE(&node->parent, parent);
            TM_STORE(&sibling->parent, parent);
        } else {
            /* Trace upwards */
            TM_STORE(&sibling->parent, parent);
            return non_leaf_insert(tree, parent, (struct bplus_node *)sibling, split_key, level + 1);
        }
    }

    return 0;
}

static long
leaf_insert(struct bplus_tree *tree, struct bplus_leaf *leaf, KEY_TYPE key, VALUE_TYPE data)
{
    long i, j, split = 0;
    struct bplus_leaf *sibling;

    long insert = key_binary_search(leaf->key, TM_LOAD(&leaf->entries), key);
    if (insert >= 0) {
        /* Already exists */
        TM_STORE(&leaf->data[insert], data);
        return 0;
    }
    insert = -insert - 1;
    int tree_entries = TM_LOAD(&tree->entries);
    /* node full */
    if (TM_LOAD(&leaf->entries) == tree_entries) {
        /* split = [m/2] */
        split = (tree_entries + 1) / 2;
        /* splited sibling node */
        sibling = leaf_new();

        TM_STORE(&sibling->next, TM_LOAD(&leaf->next));
        TM_STORE(&leaf->next, sibling);
        /* leaf node's entries always equals to split after insertion */
        TM_STORE(&leaf->entries, split);
        /* sibling leaf replication due to location of insertion */
        if (insert < split) {
            /* insertion point is before split point, replicate from key[split - 1] */
            for (i = split - 1, j = 0; i < tree_entries; i++, j++) {
                TM_STORE(&sibling->key[j], TM_LOAD(&leaf->key[i]));
                TM_STORE(&sibling->data[j], TM_LOAD(&leaf->data[i]));
            }
            TM_STORE(&sibling->entries, j);
            /* insert new key and sub-node */
            for (i = split - 1; i > insert; i--) {
                TM_STORE(&leaf->key[i], TM_LOAD(&leaf->key[i - 1]));
                TM_STORE(&leaf->data[i], TM_LOAD(&leaf->data[i - 1]));
            }
            TM_STORE(&leaf->key[i], key);
            TM_STORE(&leaf->data[i], data);
        } else {
            /* insertion point is or after split point, replicate from key[split] */
            for (i = split, j = 0; i < tree_entries; j++) {
                if (j != insert - split) {
                    TM_STORE(&sibling->key[j], TM_LOAD(&leaf->key[i]));
                    TM_STORE(&sibling->data[j], TM_LOAD(&leaf->data[i]));
                    i++;
                }
            }
            /* reserve a hole for insertion */
            if (j > insert - split) {
                TM_STORE(&sibling->entries, j);
            } else {
                assert(j == insert - split);
                TM_STORE(&sibling->entries, j + 1);
            }
            /* insert new key */
            j = insert - split;
            TM_STORE(&sibling->key[j], key);
            TM_STORE(&sibling->data[j], data);
        }
    } else {
        /* simple insertion */
        long entries = TM_LOAD(&leaf->entries);
        for (i = entries; i > insert; i--) {
            TM_STORE(&leaf->key[i], TM_LOAD(&leaf->key[i - 1]));
            TM_STORE(&leaf->data[i], TM_LOAD(&leaf->data[i - 1]));
        }
        TM_STORE(&leaf->key[i], key);
        TM_STORE(&leaf->data[i], data);
        TM_STORE(&leaf->entries, entries+1);
    }
    if (split) {
        struct bplus_non_leaf *parent = (struct bplus_non_leaf*)TM_LOAD(&leaf->parent);
        if (parent == NULL) {
            /* new parent */
            parent = non_leaf_new();
            TM_STORE(&parent->key[0], TM_LOAD(&sibling->key[0]));
            TM_STORE(&parent->sub_ptr[0], (struct bplus_node *)leaf);
            TM_STORE(&parent->sub_ptr[1], sibling);
            TM_STORE(&parent->children, 2);
            /* update root */
            TM_STORE(&tree->root, parent);
            TM_STORE(&tree->head[1], parent);
            TM_STORE(&leaf->parent, parent);
            TM_STORE(&sibling->parent, parent);
        } else {
            /* trace upwards */
            TM_STORE(&sibling->parent, parent);
            return non_leaf_insert(tree, parent, (struct bplus_node *)sibling, TM_LOAD(&sibling->key[0]), 1);
        }
    }

    return 0;
}

static long
bplus_tree_insert(struct bplus_tree *tree, KEY_TYPE key, VALUE_TYPE data)
{
    long i;
    struct bplus_node *node = (struct bplus_node*)TM_LOAD(&tree->root);

    struct bplus_non_leaf *nln;
    struct bplus_leaf *ln, *root;

    while (node != NULL) {
        switch (TM_LOAD(&node->type)) {
            case BPLUS_TREE_NON_LEAF:
                nln = (struct bplus_non_leaf *)node;

                i = key_binary_search(nln->key, TM_LOAD(&nln->children) - 1, key);
                if (i >= 0) {
                    node = (struct bplus_node*)TM_LOAD(&nln->sub_ptr[i + 1]);
                } else {
                    i = -i - 1;
                    node = (struct bplus_node*)TM_LOAD(&nln->sub_ptr[i]);
                }
                break;
            case BPLUS_TREE_LEAF:
                ln = (struct bplus_leaf *)node;
                return leaf_insert(tree, ln, key, data);
            default:
                assert(0);
        }
    }

    /* new root */
    root = leaf_new();
    TM_STORE(&root->key[0], key);
    TM_STORE(&root->data[0], data);
    TM_STORE(&root->entries, 1);

//    tree->head[0] = (struct bplus_node *)root;
//    tree->root = (struct bplus_node *)root;
    TM_STORE(&tree->head[0], root);
    TM_STORE(&tree->root, root);
    return 0;
}


void report_tree(struct bplus_tree* tree){
   
    int i, j;
    int leafs = 0;
    int nodes = 0;
    for (i = tree->level - 1; i > 0; i--) {
            struct bplus_non_leaf *node;
            node = (struct bplus_non_leaf *)TM_LOAD(&tree->head[i]);
            if (node != NULL) {
                printf("LEVEL %d:\n", i);
                while (node != NULL) {
                    nodes++;
                    node = (struct bplus_non_leaf *)TM_LOAD(&node->next);
                }
            }
    }
    struct bplus_leaf *leaf;
    leaf = (struct bplus_leaf *)TM_LOAD(&tree->head[0]);
    if (leaf != NULL) {
            printf("LEVEL 0:\n");
            while (leaf != NULL) {
                leafs++;
                leaf = (struct bplus_leaf*)TM_LOAD(&leaf->next);
            }
    } else {
            printf("Empty tree!\n");
    }
    int size = leafs*sizeof(struct bplus_leaf) + nodes*sizeof(struct bplus_non_leaf);
    printf("leafs: %d,  nodes: %d,  total size: %d\n", leafs, nodes, size);
}
void
bplus_tree_dump(struct bplus_tree *tree)
{       
        int i, j;
        long sum = 0;

        for (i = tree->level - 1; i > 0; i--) {
                struct bplus_non_leaf *node = (struct bplus_non_leaf *)TM_LOAD(&tree->head[i]);
                if (node != NULL) {
                        printf("LEVEL %d:\n", i);
                        while (node != NULL) {
                                printf("node: %ld ", TM_LOAD(&node->children));
                                for (j = 0; j < TM_LOAD(&node->children); j++) {
                                //        printf("%ld ", TM_LOAD(&node->key[j]));
                                }
                                printf("\n");
                                node = (struct bplus_non_leaf *)TM_LOAD(&node->next);
                        }
                }
        }

        struct bplus_leaf *leaf = (struct bplus_leaf *)TM_LOAD(&tree->head[0]);
        if (leaf != NULL) {
                printf("LEVEL 0:\n");
                while (leaf != NULL) {
                        printf("leaf: ");
                        sum += leaf->entries;
                        for (j = 0; j < TM_LOAD(&leaf->entries); j++) {
                        //        printf("%ld-%p ", TM_LOAD(&leaf->key[j]), (void*)TM_LOAD(&leaf->data[j]));
                        }
                        printf("\n");
                        leaf = (struct bplus_leaf*)TM_LOAD(&leaf->next);
                }
        } else {
                printf("Empty tree!\n");
        }
        printf("[SUM]%ld", sum);
}

VALUE_TYPE
bplus_tree_get(struct bplus_tree *tree, KEY_TYPE key)
{
        VALUE_TYPE data;
        data = bplus_tree_search(tree, key);
        return data;
}

long
bplus_tree_put(struct bplus_tree *tree, KEY_TYPE key, VALUE_TYPE data)
{       
        long result;
        result = bplus_tree_insert(tree, key, data);
        return result;
}

struct bplus_tree *
bplus_tree_init(int level, int order, int entries)
{
        /* The max order of non leaf nodes must be more than two */
        assert(MAX_ORDER > MIN_ORDER);
        assert(level <= MAX_LEVEL && order <= MAX_ORDER && entries <= MAX_ENTRIES);

        struct bplus_tree *tree = (struct bplus_tree*)PMALLOC(sizeof(*tree));
        if (tree != NULL) {
                TM_STORE(&tree->root, NULL);
                TM_STORE(&tree->level, level);
                TM_STORE(&tree->order, order);
                TM_STORE(&tree->entries, entries);
//                memset(tree->head, 0, MAX_LEVEL * sizeof(struct bplus_node *));
        }
        for(int i=0; i<level; i++){
            TM_STORE(&tree->head[i], NULL);
        }

        return tree;
}

int bplus_tree_size(struct bplus_tree *tree){
    struct bplus_leaf* node = (struct bplus_leaf*)tree->head[0];
    int size = 0;
    while(node){
        size += node->entries;
        node = node->next;
    }
    return size;
}

int main() {
	struct bplus_tree* tree  = bplus_tree_init(10, 32, 32);
	unsigned short seed[3];
	seed[0] = rand();
	seed[1] = rand();
	seed[2] = rand();

	for (int i = 0; i < 100000; i ++ ) {
		long d  = (long)(erand48(seed)* 0xffffffff);
		printf("%ld\n", d);
		bplus_tree_put(tree, d, d);
	}

	bplus_tree_dump(tree);

	return 0;
}
