//生产者与消费者模型
///此处是单生产者与单消费者（同步且互斥）
//生产者与消费者关系：同步且互斥
//生产者与生产者：互斥
//消费者与消费者：互斥
//基于阻塞队列
#include "pthread.hpp"

#define NUM 8
void* consum_rou(void* arg)
{
  BlockQueue * bq = (BlockQueue*)arg;
  for(;;)
  {
    int data = 0;
    bq->Pop(data);
    cout<<"consum is done "<<data<<endl;
  }


}
void* product_rou(void* arg)
{
  BlockQueue * bq = (BlockQueue *)arg;

  srand((unsigned)time(NULL));
  for(;;)
  {
    int data = rand()%100+1;
    bq->Push(data);
    cout<<"product is done "<<data<<endl;

  }

}

int main()
{
  BlockQueue* bq = new BlockQueue(NUM);
  
  pthread_t c,p;
  pthread_create(&c ,NULL,consum_rou,(void*)"pthread consum");
  pthread_create(&p,NULL,product_rou,(void*)"pthread product");

  pthread_join(c,NULL);
  pthread_join(p,NULL);

  delete(bq);
  return 0;
}
