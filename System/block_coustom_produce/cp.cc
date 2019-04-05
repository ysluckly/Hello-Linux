#include "cp.hpp"

const int num = 10;

using namespace std;

void *consume_routine(void *arg)
{
    BlockQueue *bqp = (BlockQueue*)arg;
    int data;
    for(;;){
        bqp->PopData(data);
        cout << "consume done, data is : " << data << endl;
    }
}

void *product_routine(void *arg)
{
    BlockQueue *bqp = (BlockQueue*)arg;
    srand((unsigned long)time(NULL));
    for(;;){
        int data = rand()%100 + 1;
        bqp->PushData(data);
        cout << "product done, data is : " << data << endl;
        usleep(100000);
    }
}

int main()
{
    BlockQueue *bqp = new BlockQueue(num);
    pthread_t c, p;
    pthread_create(&c, NULL, consume_routine, (void *)bqp);
    pthread_create(&p, NULL, product_routine, (void *)bqp);


    pthread_join(c, NULL);
    pthread_join(p, NULL);
    delete(bqp);
}





