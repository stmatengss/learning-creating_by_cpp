#include <stdio.h>
#include <string.h>

struct test {
	int id;
	long key;
	char data[]; // 
};

const long data_size = 8;

int main() {
	struct test *t = (struct test *)malloc(sizeof(struct test) + data_size);

	t->id = 10;
	t->key = 10ULL;
	memset(t->data, 'a', data_size);
	
	printf("%s", t->data);

	return 0;
}
