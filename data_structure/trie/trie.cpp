#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

const int alpha_num = 26; 

struct trie_node {
	trie_node *next[alpha_num];
	bool is_end;
	trie_node () {
		is_end = false;
	}
};

class trie {
	
	public:
	trie_node *trie_root;

	trie() {
		trie_root = new trie_node();
	}

	~trie() {

	}

	void insert(string str) {
		insert(str.c_str());
	}

	void insert(char *str) {
		int len = strlen(str);
		int counter = 0;
		auto node = trie_root;
		while (node->next[str[counter] - 'a'] && counter < len) {
			node = node->next[str[counter] - 'a'];		
			counter ++;
		}
		
		while (counter < len) {
			node->next[str[counter] - 'a'] = new trie_node();
			node = node->next[str[counter] - 'a'];
			counter ++;
		}
		
		node->is_end = true;
	
	}
	
	bool find(string str) {
		find(str.c_str());
	}

	bool find(char *str) {
		int len = strlen(str);
		int counter = 0;
		auto node = trie_root;
		while (node->next[str[counter] - 'a'] && counter < len) {
			node = node->next[str[counter] - 'a'];
			counter ++;
		}
		if (counter == len && node->is_end) {
			return true;
		}
		return false;
	}
};

int main() {
	trie *trie_obj = new trie();	
	trie_obj->insert("abc");
	trie_obj->insert("abcd");
	trie_obj->insert("bcd");
	trie_obj->insert("abde");
	cout << trie_obj->find("abc") << endl;
	cout << trie_obj->find("abcd") << endl;
	cout << trie_obj->find("bcd") << endl;
	cout << trie_obj->find("abde") << endl;
	cout << trie_obj->find("acd") << endl;
	cout << trie_obj->find("abdee") << endl;
}
