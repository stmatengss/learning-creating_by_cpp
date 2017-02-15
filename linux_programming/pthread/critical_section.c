#include <pthread.h>
#include <stdio.h>
#include <string.h>

float* account_balances;

int process_trasaction(int from_acct, int to_acct, float dollars) {

		int old_cancel_state;
		if(account_balances[from_acct] < dollars) return 1;

		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

		account_balances[to_acct] += dollars;
		account_balances[from_acct] -= dollars;

		pthread_setcancelstate(old_cancel_state, NULL);

		return 0;
}

int main() {
		account_balances = (double *)malloc(sizeof(float) * 10);
		account_balances[1] = 100.0;
		account_balances[3] = 200.0;
		printf("before: from->%f, to->%f\n", account_balances[1], account_balances[3]);

		process_trasaction(1, 3, 20.0);

		printf("after: from->%f, to->%f\n", account_balances[1], account_balances[3]);

		return 0;
}
