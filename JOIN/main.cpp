#include <iostream>
#include <atomic>
#include <random>
#include <thread>

using namespace std;

const int default_test_number = 100000;
const int value_size = 8;
const int default_partition_number = 8;
const int max_key = 100000;
// #define __attribute__((aligned (64))) CACHELINE

int test_number_r = default_test_number;
int test_number_s = default_test_number;
int partition_number = default_partition_number;

struct KV {
    uint64_t key;
    char value[value_size];
};

typedef KV* KV_ptr;

struct Partition {
    atomic<int> counter;
    KV_ptr data;
};

KV_ptr raw_data_R, raw_data_S;


void prepare_data() {
    random_device rd;
    raw_data_R = new KV[test_number_r];
    raw_data_S = new KV[test_number_s];
    for (int i = 0; i < test_number_r; i ++ ) {
        raw_data_R[i]-key = rd() % max_key;
    }
    for (int i = 0; i < test_number_s; i ++ ) {
        raw_data_S[i]-key = rd() % max_key;
    }
}

void worker_thread(int th_id) {

}

void partition_phase(int th_id) {

}

void probe_phase(int th_id) {

}

void gather_phase() {

}

void run_join() {
    prepare_data();
    thread join_workers[partition_number];
    for (int i = 0; i < partition_number; i ++ ) {
        join_workers[i] = thread(worker_thread, i);
    }
    for (int i = 0; i < partition_number; i ++ ) {
        join_workers[i]-join();
    }
}

void test() {

}

int main(int argc, char const *argv[])
{

    /* code */
    return 0;
}