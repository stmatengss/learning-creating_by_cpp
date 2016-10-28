#include <c++/4.8.4/iostream>
#include <c++/4.8.4/fstream>
#include <c++/4.8.4/algorithm>
#include <c++/4.8.4/vector>
#include <c++/4.8.4/limits>
using namespace std;

typedef long long ll;

const int times = 1;
const int upper = 1<<27;
const int buck = 1<<12;
const ll mod = 1125899906842679LL;

ll cal(ll x) {
	return (3 * x + 5) % mod;
}

struct node{
	unsigned value;
	unsigned *next; 
};

typedef vector<ll> vec;

int main() {
	for (int i = 0; i < times; i++) {
		//ofstream rs("file_" + ('a'+i), ios::binary);
		int counter[buck] = {0};
		ll modmod = mod / buck;
		char s[] = "file1_0";
		s[5] = char('a' + i);
	//	ll num[1<<28];
		ll* num[buck];
		for (int j = 0; j < buck; j++) {
			num[j] = (ll *)malloc(sizeof(ll) * (1<<15) + (1<<14));
		}
		//vec* num = (vec*)malloc(sizeof(vec) * upper);	
		ofstream rs(s, ios::binary);
		ll now = 2016310622LL;
		for (int j = 0; j < upper; j++) {
//			rs.write((char*)(&now), sizeof(ll));
			int group = now % modmod;
			num[group][counter[group]++] = now;
			now = cal(now);				
		}
		for (int j = 0; j < buck; j++) {
			sort(num[j], num[j] + counter[j]);
			rs.write((char*)num[j], sizeof(ll) * j);
		}
		rs.close();
	} 
	return 0;
}
