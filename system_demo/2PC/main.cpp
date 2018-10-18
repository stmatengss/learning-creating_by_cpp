#include <iostream>
#include <atomic>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>

using namespace std;

const int ITEM_LEN = 4;

enum operation: char {
	write,
	read
};

struct log{
	char *address;
	operation op;
	char data[ITEM_LEN];
};

struct circular_log{
	const static int max_len = 1024;
	int counter;
	vector<struct log> entries;
	vector<struct log>::iterator iter;
	circular_log(): counter(0), entries(vector<struct log>(max_len)), \
					iter(entries.begin())	{
		
	}
	void append_log(struct log entry) {
//		copy_n(&entry, 1, entries[counter]);
		entries[counter ++] = entry;
		iter ++;
		if (iter == entries.end()) {
			iter = entries.begin();
		}
	}
	void append_log(char *address, operation op, char *data) {
		entries[counter].address = address;
		entries[counter].op = op;
		memcpy(data, entries[counter].data, ITEM_LEN);
		counter ++;
		iter ++;
		if (iter == entries.end()) {
			iter = entries.begin();
		}
	}
};

template<typename T>
function<bool(T)> gen_ipc_send_sig(atomic<T> atomic_var) {
	return [=](T value) {
		atomic_var = value;
		if (equal_to<T>(atomic_var, value)) return true;
		return false;
	};
}

template<typename T>
function<T()> gen_ipc_recv_sig(atomic<T> atomic_var) {
	return [=]() -> T {
		return static_cast<T>(atomic_var);	
	};
}

//bool ipc_recv_sig() {
//
//}

void coordinator() {

}

void paricipant() {

}

void test() {

}

int main() {
	return 0;
}
