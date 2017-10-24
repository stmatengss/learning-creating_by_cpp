#include <stdio.h>
#include <stddef.h> // for offsetof()

#pragma pack(push, 4)
struct st {
  char c;
  double d;
  short e;
};
#pragma pack(pop) // disables the effect of #pragma pack from now on

struct st2 {
  char c __attribute__((packed,aligned(4)));
  double d __attribute__((packed,aligned(4)));
  short e __attribute__((packed,aligned(4)));
};

int main() {
  printf("offsetof(struct st, d) = %zu\n", offsetof(struct st, d));
  printf("offsetof(struct st2, d) = %zu\n", offsetof(struct st2, d));
  printf("offsetof(struct st, e) = %zu\n", offsetof(struct st, e));
  printf("offsetof(struct st2, e) = %zu\n", offsetof(struct st2, e));
  return 0;
}
