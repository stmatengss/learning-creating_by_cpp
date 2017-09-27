#include <stdio.h>
#include <stdlib.h>

#define DEBUGP(...) printf(__VA_ARGS__)

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(format, args...) \
fprintf(stderr, format, ##args)
#else
#define DEBUG_PRINT(format, args...)
#endif

int main() {
	DEBUGP("halo: %s\n", "123");
	
	DEBUG_PRINT("num = %d\n", 123);

	return 0;
}
