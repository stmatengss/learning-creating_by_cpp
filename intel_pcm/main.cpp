#include "cpucounters.h"	// Intell PCM monitoring tool

int main() {
	PCM * m = PCM::getInstance();
	PCM::ErrorCode returnResult = m->program();
	if (returnResult != PCM::Success){
		std::cerr << "Intel's PCM couldn't start" << std::endl;
		std::cerr << "Error code: " << returnResult << std::endl;
		exit(1);
	}

	SystemCounterState before_sstate = getSystemCounterState();
	// your code
	int *ptr = new int[100000];
	for (int i = 0; i < 100000; i ++ ) {
		ptr[i] = i;
	}

	SystemCounterState after_sstate = getSystemCounterState();

	std::cout << "Instructions per clock:" << getIPC(before_sstate,after_sstate) << std::endl;
	std::cout << "Bytes read:" << getBytesReadFromMC(before_sstate,after_sstate) << std::endl;
}
