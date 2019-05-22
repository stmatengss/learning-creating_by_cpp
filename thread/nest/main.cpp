#include <thread>
#include <cstdio>
#include <vector>

using namespace std;

void echo(int tid, int mid) {
	printf("%d %d\n", tid, mid);
}

void run(int tid) {
	vector<thread> th;
	for(int i = 0; i < 2; i ++ ) {
		th.push_back(thread(echo, tid, i));
	}

	for(int i = 0; i < 2; i ++ ) {
		th[i].join();
	}
}

int main() {
		
	vector<thread> th;
	for (int i = 0; i < 2; i ++ ) {
		th.push_back(thread(run, i));
	}

	for(int i = 0; i < 2; i ++ ) {
		th[i].join();
	}	
	return 0;
}
