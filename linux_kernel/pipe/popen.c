#include <stdio.h>
#include <unistd.h>

int main() {
		FILE* stream = popen("sort", "w");

		fprintf(stream, "Fuck U\n");
		fprintf(stream, "Fuck the world\n");
}
