#include <stdio.h>
#include <stdint.h>

struct test{
    uint32_t x:1;
    uint32_t y:2;
    uint32_t z:1;
};

int main() {
    struct test t;
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
    t.x ++;
    t.y ++;
    t.z ++;
    printf("x:%d y:%d z:%d\n", t.x, t.y, t.z);
}


