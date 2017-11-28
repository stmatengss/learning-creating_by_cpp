#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <random>

const static int ValueLen = 8;
const static int IterNum = 200;

using namespace std;


struct Node {
	uint64_t key;
	char value[ValueLen];
	Node *left;
	Node *right;
};

class BST
{
public:
	Node *root;
	BST() {
		root = new Node();
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

	void test() {
		Node *now;
		int level = 0;
		int counter = 0;
		std::queue<pair<Node *, int> >q;
		q.push(make_pair(root, 0));
		while (!q.empty()) {
			auto t = q.front();
			counter ++;
			q.pop();
			if (level != t.second) {
				level = t.second;
				printf("%d\n", counter);
				counter = 0;
			}
			// printf("%lld ", (long long)t.first->key);
			if (t.first->left != nullptr) q.push(make_pair(t.first->left , t.second + 1));
			if (t.first->right!= nullptr) q.push(make_pair(t.first->right, t.second + 1));
		}
		printf("%d\n", counter);
		printf("[LEVEL]%d\n", level);
	}
};

int main(int argc, char const *argv[])
{
	BST *bst = new BST();
	random_device rd;
	int num = atoi(argv[1]);
	for (int i = 1; i < num; i ++ ) {
		// printf("[ITER]%d\n", i);
		bst->insert(i * rd() * 101 % (2 * num), nullptr);
	}
	printf("[TEST]\n");
	bst->test();
	return 0;
}
