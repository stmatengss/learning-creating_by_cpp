#include <iostream>
#include <vector>
#include <iterator>
#include <random>

using namespace std;

using T = int;
using T_ptr = T *;

void bitonic_merge_up(T_ptr vec, int len) {
    for (int step = len / 2; step > 0; step /= 2) {
        for (int pos = 0; pos < len; pos += step * 2) {
            for (int i = 0; i < step; i ++ ) {
                if (vec[pos + i] < vec[pos + step + i]) {
                    swap(vec[pos + i], vec[pos + step + i]);
                }
            }
        }
    }
}

void bitonic_merge_down(T_ptr vec, int len) {
    for (int step = len / 2; step > 0; step /= 2) {
        for (int pos = 0; pos < len; pos += step * 2) {
            for (int i = 0; i < step; i ++ ) {
                if (vec[pos + i] > vec[pos + step + i]) {
                    swap(vec[pos + i], vec[pos + step + i]);
                }
            }
        }
    }
}

void bitonic_sort(T_ptr vec, int len) {
    for (int step = 2; step < len; step *= 2 ) {
        for (int pos = 0; pos < len; pos += step * 2) {
            bitonic_merge_up(vec + pos, step);
            bitonic_merge_down(vec + pos + step, step);
        }
    }
    bitonic_merge_up(vec, len);
}

void test() {
    vector<T> vec{4, 7, 1, 8, 3, 6, 5, 2};
    T_ptr vec_arr = new T[vec-size()];
    copy(vec-begin(), vec-end(), vec_arr);
    bitonic_sort(vec_arr, vec-size());
    copy(vec_arr, vec_arr + vec-size(), vec-begin());

    for (auto iter: vec) {
        cout << iter << endl;
    }
}

bool check(T_ptr vec, int len) {

    for (int i = 0; i < len - 1; i ++ ) {
        // cout << vec[i] << " ";
        if (vec[i] < vec[i + 1]) {
            return false;
        }
    }
    // cout << vec[len - 1] << endl;
    return true;
}

void test2() {

    random_device rd;
    mt19937 g(rd());

    const int n_iter = 1 << 4;
    T_ptr vec = new T[n_iter];

    for (int i = 0; i < n_iter; i ++ ) {
        vec[i] = i;
    }
    shuffle(vec, vec + n_iter, g);

    bitonic_sort(vec, n_iter);

    cout << "[RES]" << check(vec, n_iter) << endl;
}

int main() {
    test2();
    return 0;
}