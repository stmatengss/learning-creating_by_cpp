#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <queue>
#include <random>
#include <numeric>
#include <chrono>

const static int ValueLen = 8;
const static int IterNum = 200;

using namespace std;


struct Node {
	uint64_t key;
	char value[ValueLen];
	Node *left;
	Node *right;
};

int num;

class BST
{
public:
	Node *root;
	BST() {
		root = new Node();
		root->key = 0;
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
		
	inline int binary_search(uint64_t *keys, int len) {
	 		
		return 0;
	}

	inline int binary_search(uint64_t *keys, int begin, int end) {
		return 0;
	}

	void vector_insert(uint64_t *keys, int len) {
		typedef tuple<int, int, Node *> Item;
		vector<Item> items[2];
		int round_iter = 0;
		Node *next;
//		int item_len_pre = 1;
//		int item_len_next = 0;
		int item_counter = 0;
		items[item_counter].push_back(make_tuple(0, len, root));
		while (true) {
			for (int i = 0; i < items[item_counter % 2].size(); i ++ ) {
				int begin = get<0>(items[item_counter % 2][i]);
				int end = get<1>(items[item_counter % 2][i]);
				Node *node = get<2>(items[item_counter % 2][i]);
				int mid = binary_search(keys, begin, end);
				if (node->left != nullptr) {

					items[(item_counter + 1) % 2].push_back(make_tuple(begin, mid, node->left));
				} else {
					// TODO
					// do new and insert direactly
				}
				if (node->right != nullptr) {

					items[(item_counter + 1) % 2].push_back(make_tuple(mid, end, node->right));
				} else {
					// TODO
					// do new and insert direactly
				}
			}
			items[item_counter % 2].clear();
			item_counter ++;
		}
	}

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
		q.push(make_pair(root, 0));
		while (!q.empty()) {
			auto t = q.front();
			q.pop();
			if (level != t.second) {
				level = t.second;
				sum += counter;
//				printf("[L]%d\n", counter);
				counter = 0;
			}
			counter ++;
//			printf("%lld ", (long long)t.first->key);
			if (t.first->left != nullptr) q.push(make_pair(t.first->left , t.second + 1));
			if (t.first->right!= nullptr) q.push(make_pair(t.first->right, t.second + 1));
		}
		printf("[L]%d\n", counter);
		printf("[LEVEL]%d\n", level);
		printf("[SUM]%d\n", sum);
	}
};

int main(int argc, char const *argv[])
{
	random_device rd;
	num = atoi(argv[1]);
	batch_size = atoi(argv[2]);
	uint64_t *vectors = new uint64_t[batch_size];
	BST *bst = new BST();
	int insert_counter = 0;
	auto start = std::chrono::system_clock::now();
	for (int i = 1; i < num; i ++ ) {
		// printf("[ITER]%d\n", i);
		for (int j = 0; j < batch_size; j ++ ) {

			uint64_t x = static_cast<uint64_t>(i + 1) * rd() % 10000000 + 1;
			//		printf("%d\n", x);
			auto res = bst->search(x);
			if (res == nullptr) {
				vectors[j] = x;
				insert_counter ++;
			}
		}
		bst->vector_insert(vectors, batch_size);
	}
	// bst->drop(9ULL);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TEST]\n");
	bst->test();
	printf("[TIME]%lf\n", diff.count());
	return 0;
}


