#include <iostream>

#include "zipf_gen.hpp"
#include "zipf_distribution.hpp"

using namespace std;

void test() {
    ZipfGen *zipf = new ZipfGen();
    for (int i = 0; i < 100000; i ++ ) {
        cout << zipf->next_long() << endl;
    }
}

//#define USE_DIS

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        cout << "usage: ./main alpha " << endl;
        exit(-1);
    }
    double alpha = stod(argv[1]);
    double item = stoll(argv[2]);
    double len = stoll(argv[3]);

#ifdef USE_DIS
    mt19937 rng();
    zipf_distribution<long, double> zipf1();
    for (int i = 0; i < len; i ++) {
        cout << zipf1(rng) << endl;
    }
#else
    ZipfGen *zipf = new ZipfGen(alpha, item);
    for (int i = 0; i < len; i ++ ) {
        cout << zipf->next_long() << endl;
    }
#endif
    return 0;
}
