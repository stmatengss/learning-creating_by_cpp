#include <stdio.h>

int main() {
		printf("\033[31mThis text is red \033[0mThis text has default color\n");
		printf("\033[31;43mThis text is red with yellow background \033[0mThis text has default color\n");
		return 0;
}
