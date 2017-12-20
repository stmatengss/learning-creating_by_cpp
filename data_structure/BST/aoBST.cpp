#include <algorithm>
#include <iostream>
#include <stdio.h>
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
	Node *roots[IterNum];
	Node *root;
	int root_counter;
	BST() {
		root = new Node();
		root->key = 0;
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
				new_next = new_now->left;

			} else if (key > now->key) {
				new_next = new Node();
				new_now->key = now->key;
				new_now->left = now->left;
				new_now->right = new_next;
				next = now->right;
				new_next = new_now->right;
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
	}
};

int main(int argc, char const *argv[])
{
	random_device rd;
	num = atoi(argv[1]);
	BST *bst = new BST();
	auto start = std::chrono::system_clock::now();
	vector<uint64_t>store;
	for (int i = 1; i < num; i ++ ) {
		// printf("[ITER]%d\n", i);
		uint64_t x = static_cast<uint64_t>(i) * rd() % 1000 + 1;
		//uint64_t x = static_cast<uint64_t>(i);
		printf("%d\n", x);
		store.push_back(x);
		bst->insert(x, nullptr);
	}
	// bst->drop(9ULL);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TEST]\n");
	bst->test();
	printf("[TIME]%lf\n", diff.count());
	return 0;
}


