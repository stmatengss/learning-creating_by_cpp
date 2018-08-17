#include<thread>
#include<iostream>
#define Memory_Barrier() __asm__ __volatile__("" : : : "memory")
#define ACCESS_ONCE(x) (* (volatile decltype(x) *) &(x))
using namespace std;
struct HazardPointer
{
	HazardPointer() :p_(nullptr){}
	int *p_; //Hazard Pointer
};

int *p = new int(2); 

HazardPointer *hp = new HazardPointer(); 

class Writer
{
	public:
		void retire(int *tmp) {
			retire_list = tmp;
		}
		void gc() {
			if (retire_list == hp->p_) {
			} else {
				delete retire_list;
			}
		}
		void write() {
			int *tmp = ACCESS_ONCE(p);
			p = nullptr;
			retire(tmp);
			gc();
		}
	private:
		int *retire_list;
};
class Reader
{
	public:
		void acquire(int *tmp) {
			hp->p_ = tmp;
		}
		void release() {
			hp->p_ = nullptr;
		}
		void read() {
			int *tmp = nullptr;
			do
			{
				tmp = ACCESS_ONCE(p);
				Memory_Barrier();
				acquire(tmp); 
			} while (tmp != ACCESS_ONCE(p));
			if (nullptr != tmp) { 
				cout << *tmp << endl;
			}
			release();
		}
};
int main()
{
	thread t1(&Reader::read, Reader());
	thread t2(&Writer::write, Writer());
	t1.join();
	t2.join();
	return 0;
}
