#include "tbb/tbb.h"

using namespace tbb;

void Foo(float x) {
	;;
}

class ApplyFoo {
	float *const my_a;
	public:
	void operator()( const blocked_range<size_t>& r ) const {
		float *a = my_a;
		for( size_t i=r.begin(); i!=r.end(); ++i )
			Foo(a[i]);
	}
	ApplyFoo( float a[] ) :
		my_a(a)
	{}
}; 

void ParallelApplyFoo( float a[], size_t n ) {
 	parallel_for(blocked_range<size_t>(0,n), ApplyFoo(a));
}

int main() {
	float a[] = {1.0, 2.0, 3.0, 1.0, 7.0};
	ParallelApplyFoo(a, 5);
	return 0;
}
