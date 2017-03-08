#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main () {

		printf("CPU_NUM: %ld\n", sysconf(_SC_NPROCESSORS_CONF));

		printf("PAGE_SIZE: %ld\n", sysconf(_SC_PAGESIZE));

		printf("NUM_PAGES: %ld\n", sysconf(_SC_PHYS_PAGES));

		printf("FREE_PAGES: %ld\n", sysconf(_SC_AVPHYS_PAGES));

}
