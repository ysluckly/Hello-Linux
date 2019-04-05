#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cond;

using namespace std;

void *r1(void *arg)
{
    std::string t1 = (char*)arg;
    while(1){
        pthread_cond_wait(&cond, &lock);
        cout << t1 << " is running" << endl;
    }
}

void *r2(void *arg)
{
    while(1){
        pthread_cond_signal(&cond);
        sleep(2);
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, r1, (void *)"thread 1");
    pthread_create(&t2, NULL, r2, (void *)"thread 2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
