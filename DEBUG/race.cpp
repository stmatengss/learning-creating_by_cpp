#include <pthread.h>

void *write_buffer(void *args)
{
    pthread_t *buffer = static_cast<pthread_t *>(args);
    *buffer = pthread_self();
    pthread_exit(0);
    return NULL;
}

int main()
{
    pthread_t *buffer = new pthread_t[2];
    pthread_t a, b;

    pthread_create(&a, NULL, write_buffer, buffer);
    pthread_create(&b, NULL, write_buffer, buffer);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    delete []buffer;

    return 0;
}
