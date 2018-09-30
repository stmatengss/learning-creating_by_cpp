#include <stdlib.h>
#include <stdio.h>

int main() {
	int pid = system("memcached -l 0.0.0.0 -p 10086 &");
	printf("%d\n", pid);

	return 0;
}
