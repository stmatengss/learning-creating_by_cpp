#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

char* stringToBinary(char* s, int len)
{
	if(s == NULL) return 0; /* no input string */
	char *binary = (char *)malloc(len*4);
	strcpy(binary,"");
	char *ptr = s;
	int i;

	for(; *ptr != 0; ++ptr)
	{

		/* perform bitwise AND for every bit of the character */
		for(i = 7; i >= 0; --i){
			(*ptr & 1 << i) ? strcat(binary,"1") : strcat(binary,"0");
		}


	}

	return binary;
}

int main() {

	int a = 127 * 127 * 127 * 100, b = 127 * 127 * 127 * 100, c = 63;

	char d[14];

	memcpy(d, &a, sizeof(int));
	memcpy(d + 4, &b, sizeof(int));
	memcpy(d + 8, &c, sizeof(int));

	printf("%s\n", d);
	printf("%s\n", stringToBinary(d, 12));

	return 0;
}
