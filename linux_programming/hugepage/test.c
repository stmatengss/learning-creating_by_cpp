#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <hugetlbfs.h>

int main() {
    int hpage_size = gethugepagesize();
    printf("Page Size: %d\n", hpage_size);
    void *p = get_huge_pages(hpage_size, GHP_DEFAULT);
    if (p == NULL) {
        printf("Error!\n");
        exit(0);
    }
    return 0;
}
