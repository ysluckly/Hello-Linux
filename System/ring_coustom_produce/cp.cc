#include "cp.hpp"

const int num = 16;

using namespace std;

void *consume_routine(void *arg)
{
    int d;
    RingQueue *q = (RingQueue*)arg;
    for(;;){
        q->PopData(d);
    }
}
void *product_routine(void *arg)
{
    RingQueue *q = (RingQueue*)arg;
    srand((unsigned long)time(NULL));
    for(;;){
        int d = rand()%100 + 1;
        q->PushData(d);
        sleep(1);
    }
}
int main()
{
    RingQueue *q = new RingQueue(num);
    pthread_t c, p;
    pthread_create(&c, NULL, consume_routine, (void *)q);
    pthread_create(&p, NULL, product_routine, (void *)q);


    pthread_join(c, NULL);
    pthread_join(p, NULL);
    delete(q);
}





