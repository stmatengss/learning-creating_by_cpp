#include <algorithm>
#include <vector>
#include <chrono>
//#include <execution>
#include <random>
#include <numeric>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

// all_of, none_of, any_of

auto test_print = [](int i) {cout << "Test " << i << endl;};

void test() {
	test_print(0);
	vector<int> v(10, 2);
    if (std::all_of(v.begin(), v.end(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }
}

void test1() {
	test_print(1);
	vector<int> v{1, 2, 5, 4};
	for_each(v.begin(), v.end(), [](int &n){cout << n << endl;});
	for_each(v.rbegin(), v.rend(), [](int &n){cout << n << endl;});
//	std::for_each_n(v.begin(), 3, [](int &n){cout << n << endl;});
}

void test2() {
	test_print(2);
	vector<int> v{1, 2, 5, 4};
	cout << count(v.begin(), v.end(), 2) << endl; 
	cout << count_if(v.begin(), v.end(), [](int &n){return n % 2 == 0; }) << endl; 
}

void test3() {
//	std::string in = "abcdefgh", out;
//    std::sample(in.begin(), in.end(), std::back_inserter(out),
//                5, std::mt19937{std::random_device{}()});
//    std::cout << "five random letters out of " << in << " : " << out << '\n';	
}

void test4() {
	test_print(4);
	std::vector<int> v{3, 1, 4, 1, 5, 9};
 
    std::vector<int>::iterator result = std::min_element(std::begin(v), std::end(v));
    std::cout << "min element at: " << std::distance(std::begin(v), result);
}

void test6() {
	std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
 
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Inner product of a and b: " << r1 << '\n';
 
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>());
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';
	adjacent_difference(a.begin(), a.end(), a.begin());
	for_each(a.begin(), a.end(), [](int &n){cout << n << endl;});
	cout << "====" << endl;
//	adjacent_difference(a.begin(), a.end(), [](int &m, int &n){return m - n;});
	adjacent_difference(a.begin(), a.end(), a.begin(), [](int &m, int &n){return m + n;});
	for_each(a.begin(), a.end(), [](int &n){cout << n << endl;});
	adjacent_difference(a.begin(), a.end(), a.begin(), plus<int>());
	for_each(a.begin(), a.end(), [](int &n){cout << n << endl;});
}
/*
void test5() {
	    std::vector<double> v(10'000'007, 0.5);
 
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        double result = std::accumulate(v.begin(), v.end(), 0.0);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << std::fixed << "std::accumulate result " << result
                  << " took " << ms.count() << " ms\n";
    }
 
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        double result = std::reduce(std::execution::par, v.begin(), v.end());
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << "std::reduce result "
                  << result << " took " << ms.count() << " ms\n";
    }
}
*/
int main() {
	test();
	test1();
	test2();
	test3();
	test4();
	test6();
}
