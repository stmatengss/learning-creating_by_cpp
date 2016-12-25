/*************************************************************************
    > File Name: ratio.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Dec 25 15:11:07 2016
 ************************************************************************/

#include<iostream>
#include<ratio>
using namespace std;

int main () {
	typedef ratio<1,3> one_third;
	typedef ratio<1,2> one_half;
	typedef ratio<1,4> one_fourth;
	typedef ratio_add<one_third, one_half> result;
	cout << "result = " << result::num << "/" << result::den << endl;
	cout << boolalpha;
	cout << "1/2 > 1/4?" << ratio_greater<one_half, one_fourth>::value << endl;
	return 0;
}
