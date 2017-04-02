#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main() {
		struct winsize size;
		if(isatty(STDOUT_FILENO) == 0)
				return 0;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

		printf("%d rows, %d cols\n", size.ws_row, size.ws_col);
		return 0;
}
