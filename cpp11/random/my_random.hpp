#ifndef MY_RANDOM_H_
#define MY_RANDOM_H_

#include <random>

class my_random {
	public:
	std::random_device rd;
	my_random() { }
	~my_random() { }

	template<typename T>
	T get_num(T begin, T end) {
		T gap = end - begin;
		return rd() % gap + begin;
	}	

};

#endif
