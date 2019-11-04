#include <stdio.h>
#include <stdint.h>

struct __attribute__((packed)) A {
    uint8_t a;
    uint64_t b;
    uint8_t c;
};

struct __attribute__((packed)) B {
    uint64_t b;
    uint8_t a;
    uint8_t c;
};

int main() {
    printf("A: %d\n", sizeof(struct A));
    printf("B: %d\n", sizeof(struct B));
}
