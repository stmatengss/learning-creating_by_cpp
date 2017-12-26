#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <queue>
#include <random>
#include <numeric>
#include <chrono>


using namespace std;

const static int batch_max = 100000;
const static int ValueLen = 8;
const static int IterNum = 100000;

struct Node {
	uint64_t key;
	char value[ValueLen];
	Node *left;
	Node *right;
};

int num;
int batch_size;

struct Item{
	int begin;
	int end;
	Node *father;
	Node *rep_father;
	void fill(int begin_, int end_, Node *father_, Node *rep_father_) {
		begin = begin_;
		end = end_;
		father = father_;
		rep_father = rep_father_;
	}
};

class BST
{
public:
	Node *roots[IterNum];
	Node *root;
	int root_counter;
	Item items[2][batch_max];
	BST() {
		root = new Node();
		root->key = 1000;
		roots[0] = root;
	}
	~BST() {

	}
	void insert(uint64_t key, char *value) {
		Node *next = root;
		Node *now;
		while(next != nullptr) {
			now = next;
			if (key < now->key) {
				next = now->left;
			} else if (key > now->key) {
				next = now->right;
			} else {
				// memcpy(now->value, value, ValueLen);
				return;
			}
		}
		next = new Node();
		next->key = key;
		// memcpy(next->value, value, ValueLen);
		if (key < now->key) {
			now->left = next;
		} else {
			now->right = next;
		}
	}

	inline int binary_search(uint64_t *keys, int begin, int end, int target) {
		long low = begin - 1;
		long high = end;
		while (low + 1 < high) {
			long mid = low + (high - low) / 2;
			if (target > keys[mid]) {
				low = mid;
			} else {
				high = mid;
			}
		}
		return high;
	}

	inline int binary_search(uint64_t *keys, int begin, int end) {
		return 0;
	}

	void vector_insert(uint64_t *keys, int len) {
		int round_iter = 0;
		roots[root_counter + 1] = new Node();
		roots[root_counter + 1]->key = roots[root_counter]->key;
		Node *rep_node;
		Node *new_node;
		int item_len_pre = 1;
		int item_len_next = 0;
		int item_counter = 0;
		items[item_counter][0].fill(0, len, roots[root_counter], roots[root_counter + 1]);
		while (item_len_pre > 0) {
//	printf("[%d]\n", item_counter);
//			printf("[R]%d\n", item_counter);
			for (int i = 0; i < item_len_pre; i ++ ) {
				int begin = items[item_counter % 2][i].begin;
				int end = items[item_counter % 2][i].end;
				Node *node = items[item_counter % 2][i].father;
				Node *rep_node = items[item_counter % 2][i].rep_father;
				int mid = binary_search(keys, begin, end, node->key);
//				printf("[P]%d %d %d\n", begin, end, mid);
			    if (begin == mid) {
					rep_node->left = node->left;
					// XXX
				} else {
					if (node->left != nullptr) {
						new_node = new Node();	
						new_node->key = node->left->key; 
						rep_node->left = new_node;
						items[(item_counter + 1) % 2][item_len_next ++].fill(begin, mid, node->left, new_node);
					} else {
						single_insert(rep_node, keys + begin, mid - begin);
					}
				}
				if (mid == end) {
					rep_node->right = node->right;
					//XXX
				} else {
					if (node->right != nullptr) {
						new_node = new Node();
						new_node->key = node->right->key;
						rep_node->right = new_node;
						items[(item_counter + 1) % 2][item_len_next ++].fill(mid, end, node->right, new_node);
					} else {
						single_insert(rep_node, keys + mid, end - mid);
					}
				}
			} // end for
			item_len_pre = item_len_next;
			item_len_next = 0;
			
			item_counter ++;
		}
		root_counter ++;
	}

	void single_insert(Node *node, uint64_t *candidates, int len) {
		if (len == 0)
			return;
		uint64_t key = candidates[len / 2];
		Node *now = new Node();
		now->key = key;
		Node *new_root;
		if (key < node->key) {
			node->left = now;
		} else {
			node->right = now;
		}
		new_root = now;
		int begin = 0, end = len - 1;
		for (int i = 1; i < len; i ++ ) {
			if (i % 2 == 0) {
				key = candidates[begin ++];
			} else {
				key = candidates[end ++];
			}
			Node *next = new_root;
			while(next != nullptr) {
				now = next;
				if (key < now->key) {
					next = now->left;	
				} else if (key > now->key) {
					next = now->right;
				} else {
					return;
				}
			}
			next = new Node();
			next->key = key;
			if (key < now->key) {
				now->left = next;
			} else {
				now->right = next;
			}
		}
	}
	/*
	void single_insert(Node *node, uint64_t *candidates, int len) {
		if (len == 0)
			return;
		uint64_t key = candidates[len / 2];
		Node *now = new Node();
		now->key = key;
		Node *new_root;
		if (key < node->key) {
			node->left = now;
		} else {
			node->right = now;
		}
		new_root = now;
		int begin = 0, end = len - 1;
		for (int i = 0; i < len; i ++ ) {
			if (i % 2 == 0) {

				key = candidates[begin ++];
			} else {

				key = candidates[end --];
			}
			Node *next = new_root;
			while(next != nullptr) {
				now = next;
				if (key < now->key) {
					next = now->left;	
				} else if (key > now->key) {
					next = now->right;
				} else {
					return;
				}
			}
			next = new Node();
			next->key = key;
			if (key < now->key) {
				now->left = next;
			} else {
				now->right = next;
			}
		}
	}
	*/
	char *search(uint64_t key) {
		Node *now;
		while (now != nullptr) {
			if (key < now->key) {
				now = now->left;
			} else if (key > now->key) {
				now = now->right;
			} else {
				return now->value;
			}
		}
		return nullptr;
	}

	void drop(uint64_t key) {
		Node *now = root;
		Node *parent;
		while (now != nullptr) {
			if (key < now->key) {
				parent = now;
				now = now->left;
			} else if (key > now->key) {
				parent = now;
				now = now->right;
			} else {
				break;
			}
		}
		if (now == nullptr) {
			return;
		}
		Node *left = now->left;
		Node *right = now->right;
		Node *p_left = parent->left;
		Node *p_right = parent->right;
		if (left == nullptr && right == nullptr) {
			if (p_left == now) {
				parent->left = nullptr;
			} else if (p_right == now) {
				parent->right = nullptr;
			}
			delete now;
		} else if (left == nullptr && right != nullptr) {
			if (p_left == now) {
				parent->left = right;
			} else if (p_right == now) {
				parent->right = right;
			}
			delete now;
		} else if (left != nullptr && right == nullptr) {
			if (p_left == now) {
				parent->left = left;
			} else if (p_right == now) {
				parent->right = left;
			}
			delete now;
		} else {
			
			if (right->left == nullptr && right->right == nullptr) {
				if (p_left == now) {
					parent->left = right;
					right->left = now->left;
					delete now;
				} else if (p_right == now) {
					parent->right = right;
					right->left = now->left;
					delete now;
				}
			} else if (right->left != nullptr) {
				Node *l_parent = right;
				Node *l_now = right->left;
				while (l_now->left != nullptr) {
					l_parent = l_now;
					l_now = l_now->left;
				}
				now->key = l_now->key;
				// memcpy(now->value, l_now->key, ValueLen);
				delete l_now;
				l_parent->left = nullptr;
			} else {
				right->left = left;
				if (p_left == now) {
					parent->left = right;
					right->left = now->left;
					delete now;
				} else if (p_right == now) {
					parent->right = right;
					right->left = now->left;
					delete now;
				}
			}
		}
	}

	void test() {
		Node *now;
		int level = 0;
		int counter = 0;
		int sum = 0;
		std::queue<pair<Node *, int> >q;
//		q.push(make_pair(root, 0));
		q.push(make_pair(roots[root_counter], 0));
		while (!q.empty()) {
			auto t = q.front();
			q.pop();
			if (level != t.second) {
				level = t.second;
				sum += counter;
				printf("[L]%d\n", counter);
				counter = 0;
			}
			counter ++;
//			printf("%lld ", (long long)t.first->key);
			if (t.first->left != nullptr) q.push(make_pair(t.first->left , t.second + 1));
			if (t.first->right!= nullptr) q.push(make_pair(t.first->right, t.second + 1));
		}
		sum += counter;
		printf("[L]%d\n", counter);
		printf("[LEVEL]%d\n", level);
		printf("[SUM]%d\n", sum);
	}
};

#define BATCH
const static int pre_insert = 1000000;

int main(int argc, char const *argv[])
{
	random_device rd;
	num = atoi(argv[1]);
	batch_size = atoi(argv[2]);
	uint64_t *vectors = new uint64_t[batch_size];
	BST *bst = new BST();
	int insert_counter = 0;
	/*
	for (int i = 0; i < pre_insert; i ++ ) {
		uint64_t x = static_cast<uint64_t>(i + 1) * rd() % 100000000 + 1;
		bst->insert(x, nullptr);
	}
	*/
	auto start = std::chrono::system_clock::now();
#ifdef BATCH
	for (int i = 0; i < num; i ++ ) {
//		printf("[ITER]%d\n", i);
		for (int j = 0; j < batch_size; j ++ ) {

			uint64_t x = static_cast<uint64_t>(i + 1) * rd() % 100000000 + 1;
//			printf("%d\n", x);
//			auto res = bst->search(x);
//			if (res == nullptr) {
				vectors[j] = x;
				insert_counter ++;
//			}
		}
		sort(vectors, vectors + batch_size);
//		for (int j = 0; j < batch_size; j ++ ) {
//			printf("%lld\n", vectors[j]);
//		}
		bst->vector_insert(vectors, batch_size);
//		printf("\n");
//		bst->test();
//		printf("\n");
	}
#else
	for (int i = 0; i < num * batch_size; i ++ ) {

		uint64_t x = static_cast<uint64_t>(i + 1) * rd() % 100000000 + 1;
		bst->insert(x, nullptr);
	}
#endif
	// bst->drop(9ULL);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TEST]\n");
	bst->test();
	printf("[TIME]%lf\n", diff.count());
	return 0;
}


