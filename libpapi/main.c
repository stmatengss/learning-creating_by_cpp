#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

#define PAPI_COUNTER PAPI_L1_ICM
//#define PAPI_COUNTER PAPI_TOT_INS

double your_slow_code() {
  int i;
  int tmp = 1;

  for (i = 1; i < 100000000; i++) {
    tmp = (tmp + 100) % i;
  }

  return tmp;
}

void papi_start(void) {
  int counters[] = {PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_COUNTER};
  if (PAPI_start_counters(counters, 3) != PAPI_OK) {
    fprintf(stderr, "Error initializing counters.\n");
    exit(-1);
  }
}

void papi_mark(void) {
  long long final_count[3];
  if (PAPI_read_counters(final_count, 3) != PAPI_OK) {
    fprintf(stderr, "Error reading instruction count\n");
    exit(-1);
  } else {
    printf("Total cycles = %lld\n", final_count[0]);
    printf("Total instructions = %lld. IPC = %.2f.\n", final_count[1],
        final_count[1] * 1.0 / final_count[0]);
    printf("Total [general counter] = %lld\n", final_count[2]);
  }
}

int main() {
  papi_start();
  double sum = your_slow_code();
  papi_mark();

  printf("Sum = %f\n", sum);
}
