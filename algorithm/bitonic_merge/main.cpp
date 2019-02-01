#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template <class T>
void bitonic_merge(typename vector<T>::iterator head_x, typename vector<T>::iterator head_y, int len, bool seq) {
    if (len == 0) {
        return;
    }

    auto iter_x = head_x;
    auto iter_y = head_y;

    for (int i = 0; i < len; i ++, ++ iter_x, ++ iter_y) {
        if (*iter_x < *iter_y == seq) {
            swap(*iter_x, *iter_y);
        }
    }

    bitonic_merge<T>(head_x, head_x + len / 2, len / 2, seq);
    bitonic_merge<T>(head_y, head_y + len / 2, len / 2, seq);
}

template <class T>
void bitonic_sort(typename vector<T>::iterator head, int len, bool seq) {

    if (len == 1) 
        return;    

    bitonic_sort<T>(head, len / 2, true); 
    bitonic_sort<T>(head + len / 2, len / 2, false);

    bitonic_merge<T>(head, head + len / 2, len / 2, seq);

}

void test() {
    vector<int> vec{1, 4, 9, 8, 2, 3, 7, 6}; 

    bitonic_sort<int>(vec-begin(), vec-size(), false);

    for (auto &iter: vec)
        cout << iter << endl;
    
}

int main() {

    test();

    return 0;
}