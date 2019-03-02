#include <stdio.h>

int main()
{
    volatile int i = 0;
    while (i < 100000000) {
        __asm__ ("xbegin ABORT");
        i++;
        __asm__ ("xend");
        __asm__ ("ABORT:");
    }

    printf("%d\n", i);
    return 0;
}
