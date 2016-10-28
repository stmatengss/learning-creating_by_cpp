#include <c++/4.8/iostream>
#include <omp.h>

using namespace std;
static long num_steps = 100000;
double step;
void test2 ()
{	
	int i; 
	double x, pi, sum = 0.0;
	step = 1.0/(double) num_steps;
	for (i=0; i< num_steps; i++){
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x); }
	pi = step * sum;
}
void work(float* c, float* a, float* b, int N) {
	float x, y; int i;
#pragma omp parallel for private(x,y) 
	for(i=0; i<N; i++) {
		x = a[i];
		y = b[i];
		c[i] = x + y;
	}
}

void test() {
	int i;
#pragma omp parallel for schedule(static, 2)
	for (i = 0; i < 30; i++) {
		cout<<"num="<<omp_get_thread_num()<<endl;
	}
}


int main() {
	//test();
//	float a[5] = {1, 2, 3, 4, 5};
//	float b[5] = {1, 2, 3,4, 5};
	test2();
//	float c[5];      
//	work(c, a, b, 5);
	return 0;
}
