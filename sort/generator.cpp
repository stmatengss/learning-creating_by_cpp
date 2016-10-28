#include <c++/4.8.4/iostream>
#include <c++/4.8.4/fstream>
#include <c++/4.8.4/algorithm>

using namespace std;

typedef long long ll;

const int times = 1;
const int upper = 1<<27;
const ll mod = 1125899906842679LL;

ll cal(ll x) {
	return (3 * x + 5) % mod;
}

int main() {
	for (int i = 0; i < times; i++) {
		//ofstream rs("file_" + ('a'+i), ios::binary);
		char s[] = "file_0";
		s[5] = char('a' + i);
	//	ll num[1<<28];
		ll* num = (ll*)malloc(sizeof(ll) * upper);	
		ofstream rs(s, ios::binary);
		ll now = 2016310622LL;
		for (int j = 0; j < upper; j++) {
//			rs.write((char*)(&now), sizeof(ll));
			num[j] = now;
			now = cal(now);				
		}
		sort(num, num + upper);
		rs.write((char*)num, sizeof(ll) * upper);
		rs.close();
	} 
	return 0;
}
