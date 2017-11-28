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
				printf("%d\t%.2lf\n", counter, static_cast<double>(counter) * 100 / num);
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
	num = atoi(argv[1]);
	auto start = std::chrono::system_clock::now();
	for (int i = 1; i < num; i ++ ) {
		// printf("[ITER]%d\n", i);
		bst->insert(i * rd() * 101 % (1 * num), nullptr);
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TEST]\n");
	bst->test();
	printf("[TIME]%lf\n", diff.count());
	return 0;
}
