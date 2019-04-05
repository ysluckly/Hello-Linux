#ifndef __CP_HPP__
#define __CP_HPP__

#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

class BlockQueue{
    private:
        std::queue<int> bq;
        int cap;

        pthread_mutex_t lock;
        pthread_cond_t  cond_p;//queue empty
        pthread_cond_t  cond_c;//queue full

        int water_line;
    private:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        void ProductWait()
        {
            pthread_cond_wait(&cond_p, &lock);
        }
        void ConsumeWait()
        {
            pthread_cond_wait(&cond_c, &lock);
        }
        bool IsFull()
        {
            return bq.size() == cap ? true : false;
        }
        bool IsEmpty()
        {
            return bq.size() == 0 ? true : false;
        }
        void SignalConsume()
        {
            pthread_cond_signal(&cond_c);
        }
        void SignalProduct()
        {
            pthread_cond_signal(&cond_p);
        }
        bool IsHighWaterLine()
        {
            return bq.size() > water_line ? true:false;
        }
    public:
        BlockQueue(int cap_):cap(cap_),water_line(cap_*2/3)
        {
            pthread_mutex_init(&lock, NULL);
            pthread_cond_init(&cond_p, NULL);
            pthread_cond_init(&cond_c, NULL);
        }
        void PushData(const int &data)
        {
            LockQueue();
            while(IsFull()){
                ProductWait();
            }
            bq.push(data);
            if(IsHighWaterLine()){
                SignalConsume();
            }
            UnlockQueue();
        }
        void PopData(int &data)
        {
            LockQueue();
            while(IsEmpty()){
                SignalProduct();
                ConsumeWait();
            }
            data = bq.front();
            bq.pop();
            UnlockQueue();
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond_p);
            pthread_cond_destroy(&cond_c);
        }

};

#endif











