#include <iostream>
#include <cstdio>

using namespace std;

class F{
    public:
        F() {

        }
        ~F() {

        }
        int fuck;
};

int main() {
    auto p = new char[1<<10];
    auto f = new (p) F();
    return 0;
}
