#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

double your_slow_code() {
  int i;
  double tmp = 1.1;

  for (i = 1; i < 100000000; i++) {
    tmp = (tmp + 100) / i;
  }

  return tmp;
}

int main() {
  float real_time, proc_time, ipc;
  long long ins;
  float real_time_i, proc_time_i, ipc_i;
  long long ins_i;
  int retval;

  if ((retval = PAPI_ipc(&real_time_i, &proc_time_i, &ins_i, &ipc_i)) <
      PAPI_OK) {
    printf("Could not initialise PAPI_ipc \n");
    printf("retval: %d\n", retval);
    exit(1);
  }

  double ans = your_slow_code();

  if ((retval = PAPI_ipc(&real_time, &proc_time, &ins, &ipc)) < PAPI_OK) {
    printf("retval: %d\n", retval);
    exit(1);
  }

  printf("Real_time: %f Proc_time: %f Total instructions: %lld IPC: %f\n",
         real_time, proc_time, ins, ipc);

  PAPI_shutdown();
  printf("Loop sum = %f\n", ans);
  exit(0);
}
