#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <event.h>

using namespace std;

void say(int sock, short event, void *argv) {
		cout << "Fuck" << endl;

		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		event_add((struct event*) argv, &tv);
}

int main() {

		event_init();

		struct event evTime;

		evtimer_set(&evTime, say, &evTime);

		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		event_add(&evTime, &tv);

		event_dispatch();

		return 0;
}
