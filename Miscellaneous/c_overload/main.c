#include <stdio.h>
#include <stdarg.h>

void va_overload2(int p1, int p2)
{

	printf("va_overload2 %d %d\n", p1, p2);
}

void va_overload3(int p1, int p2, int p3)
{

	printf("va_overload3 %d %d %d\n", p1, p2, p3);
}

static void va_overload(int p1, int p2, ...)
{

	if (p2 == 3)
	{

		va_list v;
		va_start(v, p2);

		int p3 = va_arg(v, int);
		va_end(v);
		va_overload3(p1, p2, p3);

		return;
	}

	va_overload2(p1, p2);
}

int main()
{

	va_overload(1, 2);
	va_overload(1, 2, 3);
	return 0;
}
