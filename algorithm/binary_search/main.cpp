#include <iostream>
#include <stdio.h>

using namespace std;

long
key_binary_search(long *arr, long len, long target)
{
	long low = -1;
	long high = len;
	while (low + 1 < high) {
		long mid = low + (high - low) / 2;
		if (target > arr[mid]) {
			low = mid;
		} else {
			high = mid;
		}
	}
	if (high >= len || arr[high] != target) {
		return -high - 1;
	} else {
		return high;
	}
}

int main() {
	long arr[] = {
		1, 1, 3, 3, 5, 6
	};
	printf("%d\n", key_binary_search(arr, 6, 4));
	return 0;
}
