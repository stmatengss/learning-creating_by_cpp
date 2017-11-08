#include <pthread.h>

pthread_mutex_t mutex;

void *still_locked(void *args)
{
    (void)args;
    pthread_mutex_lock(&mutex);
    pthread_exit(0);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t a;
    pthread_create(&a, NULL, still_locked, NULL);
    pthread_join(a, NULL);
    return 0;
}
