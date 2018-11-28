  
#ifndef __HPP_H__
#define __HPP_H__

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <time.h>

using namespace std;

class BlockQueue
{
  private:
    queue<int> bq;
    int _cap;
    
    pthread_mutex_t mutex;
    pthread_cond_t p_cond;//empty
    pthread_cond_t c_cond;//full

  private:
    void LockQueue()
    {
      pthread_mutex_lock(&mutex);
    }
    
    void UnlockQueue()
    {
      pthread_mutex_unlock(&mutex);
    }
    void SignalProduct()
    {
      pthread_cond_signal(&p_cond);

    }
    void SignalConsum()
    {
      pthread_cond_signal(&c_cond);

    }
    void ProductWait()
    {
      pthread_cond_wait(&p_cond,&mutex);
    }

    void ConsumWait()
    {
      pthread_cond_wait(&c_cond,&mutex);
    }
    bool IsFull()
    {
      return bq.size() == _cap ? true : false;

    }
    bool IsEmpty()
    {
      return bq.size() == 0 ? true : false;
    }


  public:
    BlockQueue(const int& cap)
      :_cap(cap)
    {
      pthread_mutex_init(&mutex,NULL);
      pthread_cond_init(&p_cond,NULL);
      pthread_cond_init(&c_cond,NULL);

    }
    void Push(const int& data)
    {
      LockQueue();
      while(IsFull())
      {
        ProductWait();
        SignalConsum();
      }

        bq.push(data);

      UnlockQueue();

    }

    void Pop(int &data)
    {
      LockQueue();
      while(IsEmpty())
      {
        ConsumWait();
        SignalProduct();
      }
      data = bq.front();
      bq.pop();
      UnlockQueue();
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&mutex);
      pthread_cond_destroy(&p_cond);
      pthread_cond_destroy(&c_cond);

    }

};



#endif //__HPP_H__
