#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

typedef void (*_hanlder)(int);
class Task{

  private:
    int sock;
   _hanlder hanlder;
  public:
   Task(const int& _sock,_hanlder h):sock(_sock),hanlder(h)
  {

  }
   void Run()
   {
     hanlder(sock);
   }
   ~Task()
   {

   }
};


class ThreadPool
{
  private:
    int thread_num;
    int idle_num;//状态
    queue<Task> task_queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;

  public:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }

    void UnLockQueue()
    {
        pthread_mutex_unlock(&lock);
    }
    bool IsQueueEmpty()
    {
        return task_queue.size() == 0;
    }

    void IdleThread()//线程等待
    {
      pthread_cond_wait(&cond,&lock);//等待释放锁，唤醒高优先级拿到锁

    }
    void WakeUpOneThead()
    {
      pthread_cond_signal(&cond);
    }
    void TaskPop(Task& t)
    {
      t = task_queue.front();
      task_queue.pop();

    }
  public:
    ThreadPool(int _num):thread_num(_num),idle_num(0)
    {

        pthread_mutex_init(&lock,NULL);
        pthread_cond_init(&cond,NULL);
    }

    void AddTask(const Task& t)
    {
      LockQueue();

      task_queue.push(t);
      //需要唤醒一个
      WakeUpOneThead();
      UnLockQueue();

    }
    void  InitThreadPool()
    {
      pthread_t tid;
       for(auto i = 0;i<thread_num;++i)
      {
        pthread_create(&tid,NULL,ThreadRoutine,this);

      }

    }
    static void* ThreadRoutine(void* arg)
    {
      ThreadPool *tp = (ThreadPool*)arg;
      pthread_detach(pthread_self());
      for(;;)
      {
        tp->LockQueue();

        while(tp->IsQueueEmpty())//while题代if，因为函数可能异常唤醒，唤醒依然为空，需要仍继续检测
        {
          tp->IdleThread();//处于edle状态
        }
        Task t(-1,NULL);
        tp->TaskPop(t);
        tp->UnLockQueue();
        //run放置在外面，为了同时处理多个任务，否则只能同时处理一个
        t.Run();
        
      }
    }
    ~ThreadPool()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);

    }
};
