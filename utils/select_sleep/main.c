#include <stdint.h>
#include <sys/select.h>
#include <stdlib.h>
#include <string.h>

static void select_sleep (uint64_t usec) {
    if (usec <= 10) return;
    fd_set fd;
    int max_fd=0;
    struct timeval tv;
    tv.tv_sec = usec / 1000000;
    tv.tv_usec = usec % 1000000;
    FD_ZERO (&fd);
    select (max_fd, &fd, NULL, NULL, &tv);
    // on Linux, tv reflects the actual time slept.
}


int main() {
    select_sleep(10000000);
    return 0;
}
