#ifndef __CP_HPP__
#define __CP_HPP__

#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

class RingQueue{
    private:
        std::vector<int> ring;
        int cap;
        sem_t blank_sem;
        sem_t data_sem;

        int c_step;
        int p_step;
    private:
        void P(sem_t &sem)
        {
            sem_wait(&sem);
        }
        void V(sem_t &sem)
        {
            sem_post(&sem);
        }
    public:
        RingQueue(int cap_):cap(cap_), ring(cap_)
        {
            c_step = p_step = 0;
            sem_init(&blank_sem, 0, cap_);
            sem_init(&data_sem, 0, 0);
        }
        void PushData(const int &data)
        {
            P(blank_sem);
            ring[p_step] = data;
            std::cout << "product done, data is : " << data << std::endl;
            V(data_sem);
            p_step++;
            p_step %= cap;
        }
        void PopData(int &data)
        {
            P(data_sem);
            data = ring[c_step];
            std::cout << "consume done, data is : " << data << std::endl;
            V(blank_sem);
            c_step++;
            c_step %= cap;
        }
        ~RingQueue()
        {
            sem_destroy(&blank_sem);
            sem_destroy(&data_sem);
        }
};

#endif











