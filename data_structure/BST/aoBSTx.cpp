#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <random>
#include <numeric>
#include <chrono>
#include <ext/hash_map>

const static int ValueLen = 8;
const static int IterNum = 100000000;

using namespace std;
using namespace __gnu_cxx;

typedef hash_map<uint64_t, bool> h_map;

struct Node {
	uint64_t key;
	char value[ValueLen];
	Node *left;
	Node *right;
};

int num;
int batch_size;

class BST
{
public:
	Node *roots[IterNum];
	Node *root;
	h_map is_new;

	int root_counter;
	int root_counter_batch;

	BST() {
		root = new Node();
		root->key = 0;
		roots[0] = root;
	}
	~BST() {

	}
	void insert(uint64_t key, char *value) {
		Node *next = roots[root_counter];
		Node *now;
		Node *new_next = new Node();
		roots[root_counter + 1] = new_next;
		Node *new_now;
		new_next->key = 0;

		while(next != nullptr) {
			now = next;
			new_now = new_next;
			if (key < now->key) {
				new_next = new Node();
				new_now->key = next->key;
				new_now->left = new_next;
				new_now->right = now->right;
				next = now->left;

			} else if (key > now->key) {
				new_next = new Node();
				new_now->key = now->key;
				new_now->left = now->left;
				new_now->right = new_next;
				next = now->right;

			} else {
				// memcpy(now->value, value, ValueLen);
				return;
			}
		}
		new_next->key = key;
		// memcpy(next->value, value, ValueLen);
		if (key < now->key) {
			new_now->left = new_next;
		} else {
			new_now->right = new_next;
		}
		
		root_counter ++;
	}

#if 0
	void vector_insert(uint64_t *keys, int length) {
		printf("[Insert]\n");
		Node *new_root = new Node();
		is_new.clear();
		is_new[(uint64_t)new_root] = true;
	   	roots[root_counter + 1] = new_root;	
		int key;
		
		key = keys[0];
		printf("[R]%lld\n", key);
		Node *next = roots[root_counter];
		Node *now;
		Node *new_next = new_root;
		Node *new_now;
		new_next->key = 0;

		while (next != nullptr) {
			now = next;
			new_now = new_next;
			if(key < now->key) {	
				new_next = new Node();
				is_new[(uint64_t)new_next] = true;
				new_now->key = now->key;
				new_now->left = new_next;
				new_now->right = now->right;
				next = now->left;

			} else if (key > now->key) {
				new_next = new Node();
				is_new[(uint64_t)new_next] = true;
				new_now->key = now->key;
				new_now->left = now->left;
				new_now->right = new_next;
				next = now->right;

			} else {
				return;
			}
			new_next->key = key;
			if (key < now->key) {
				new_now->left = new_next;
			} else {
				new_now->right = new_next;
			}

		}
		for (int i = 1; i < length; i ++ ) {
			testx();
			printf("[R]%lld\n", keys[i]);
			key = keys[i];
			now = new_root;
			new_now = new_root;
			Node *pre;
			Node *new_pre;
			bool status = false;	
//			while (now != nullptr) {
			while (new_now != nullptr ) {
				printf("[T]%lld\n", new_now->key);
				if (key < now->key) {
					next = now->left;
					if (next == nullptr) {
						new_pre = new_now;
						break;
					}					
					
				   	if (status) {
						new_next = new Node();
						is_new[(uint64_t)new_next] = true;
						new_next->key = next->key;

						new_now->left = new_next;
						new_now->right = now->right;
					}
					if (is_new[(uint64_t)next] == false && status == false) {
						new_next = new Node();
						is_new[(uint64_t)new_next] = true;
						new_next->key = next->key;

						new_now->left = new_next;
						status = true;
//						new_pre->left = new_now;
					}	
					new_next = new_now->left;
				} else if (key > now->key) {
					next = now->right;
					if (next == nullptr) {
						new_pre = new_now;
						break;
					}					
				   	if (status) {
						new_next = new Node();
						is_new[(uint64_t)new_next] = true;
						new_next->key = next->key;

						new_now->left = now->left;
						new_now->right = new_next;
					}	
					if (is_new[(uint64_t)next] == false && status == false) {
						new_next = new Node();
						is_new[(uint64_t)new_next] = true;
						new_next->key = next->key;

						new_now->right = new_next;
						status = true;
//						new_pre->left = new_now;
					}
					new_next = new_now->right;
				} else {
					return;
				}		
				pre = now;
				now = next;
				new_pre = new_now;
				new_now = new_next;
			}
			new_next = new Node();
			is_new[(uint64_t)new_next] = true;
			new_next->key = key;
			if (key < new_pre->key) {
				new_pre->left = new_next;
			} else {
				new_pre->right = new_next;
			}
		}
		root_counter ++;
	}

#else
	void vector_insert(uint64_t *key, int len) {
		
	}	
#endif

	char *search(uint64_t key) {
		Node *now = roots[root_counter];
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

	void testx() {
		Node *now;
		int level = 0;
		int counter = 0;
		int sum = 0;
		printf("\n");
		std::queue<pair<Node *, int> >q;
		q.push(make_pair(roots[root_counter + 1], 0));
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
			printf("%lld ", (long long)t.first->key);
			if (t.first->left != nullptr) q.push(make_pair(t.first->left , t.second + 1));
			if (t.first->right!= nullptr) q.push(make_pair(t.first->right, t.second + 1));
		}
		sum += counter;
		printf("[L]%d\n", counter);
		printf("[LEVEL]%d\n", level);
		printf("[SUM]%d\n", sum);
		printf("\n");
	}
	void test() {
		Node *now;
		int level = 0;
		int counter = 0;
		int sum = 0;
		printf("\n");
		std::queue<pair<Node *, int> >q;
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
			printf("%lld ", (long long)t.first->key);
			if (t.first->left != nullptr) q.push(make_pair(t.first->left , t.second + 1));
			if (t.first->right!= nullptr) q.push(make_pair(t.first->right, t.second + 1));
		}
		sum += counter;
		printf("[L]%d\n", counter);
		printf("[LEVEL]%d\n", level);
		printf("[SUM]%d\n", sum);
		printf("\n");
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
	for (int i = 0; i < num / batch_size; i ++ ) {
		printf("\n[BEGIN INSERT]\n");
		for(int j = 0; j < batch_size; j ++ ) {

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
	printf("[TEST]%d\n", insert_counter);
	bst->test();
	printf("[TIME]%lf\n", diff.count());
	return 0;
}


