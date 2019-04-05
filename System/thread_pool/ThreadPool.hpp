 #ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
using namespace std;

typedef int (*cal_t)(int ,int);
class Task{
    private:
        int x;
        int y;
        cal_t handler_task;
        int z;
    public:
        Task(int x_, int y_, cal_t handler_task_)
            :x(x_), y(y_), handler_task(handler_task_)
        {
        }
        void Run()
        {
            z= handler_task(x, y);
        }
        void Show()
        {
            //for test
            cout << "thread " << pthread_self() << " Handler Task done. "<< "Result is : " << z << endl; // for test
        }
        ~Task()
        {
        }
};

class ThreadPool{
    private:
        int thread_nums;
        //int idles;
        std::queue<Task> t_queue;
        pthread_mutex_t lock;
        pthread_cond_t cond;
        bool is_stop;
    private:
        static void *thread_routine(void *arg)
        {
            ThreadPool *tp = (ThreadPool*)arg;
            pthread_detach(pthread_self());
            for(;;){
                tp->LockQueue();
                while(tp->IsEmpty()){
                    tp->IdleThread();
                }
                Task t = tp->GetTask();
                tp->UnlockQueue();

                t.Run();                     // for test
                t.Show();
            }
        }
        void NotifyOneThread()
        {
            pthread_cond_signal(&cond);
        }
        void NotifyAllThreads()
        {
            pthread_cond_broadcast(&cond);
        }
    public:
        ThreadPool(int num_):thread_nums(num_), is_stop(false)
        {}
        void InitThreadPool()
        {
            pthread_mutex_init(&lock, NULL);
            pthread_cond_init(&cond, NULL);
            int i = 0;
            for(; i < thread_nums; i++){
                pthread_t tid;
                pthread_create(&tid, NULL, thread_routine, (void *)this);
            }
        }
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        bool IsEmpty()
        {
            return t_queue.size() == 0 ? true : false;
        }
        void IdleThread()
        {
            if(is_stop){
                UnlockQueue();
                thread_nums--;
                pthread_exit((void *)0);
                cout << "pthread " << pthread_self() << " quit!" << endl; //for test
                return;
            }
            pthread_cond_wait(&cond, &lock);
        }
        void AddTask(Task &t)
        {
            LockQueue();
            if(is_stop){
                UnlockQueue();
                return;
            }
            t_queue.push(t);
            NotifyOneThread();
            UnlockQueue();
        }
        Task GetTask()
        {
            Task t = t_queue.front();
            t_queue.pop();
            return t;
        }
        void Stop()
        {
            LockQueue();
            is_stop = true;
            UnlockQueue();
            while(thread_nums > 0){
                NotifyAllThreads();
            }
        }
        ~ThreadPool()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond);
        }
};


#endif
