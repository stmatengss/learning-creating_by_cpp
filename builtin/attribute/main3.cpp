#include <chrono>
#include <cstdio>

#define OPT "O0"

const int iter = 10000000;

void __attribute__((optimize(OPT)))
	fuck() {


		int i = 0, sum = 0;
		int arr[iter];
		for (; i < iter; i ++) {
			arr[i] = sum;
			sum += i;
			int tmp = 0;
			for (int j = 0; j < 100; j ++ ) {
				tmp += j;
			}
			sum += tmp;
		}   
	}

int main() {

	auto start = std::chrono::system_clock::now();
	fuck();
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("%lf\n", diff.count());

	return 0;
}
