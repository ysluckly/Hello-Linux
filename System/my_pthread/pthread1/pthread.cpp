#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
void* pthread_hander(void* arg)
{

    const char* pthread_name =(char*)arg;
    sleep(3);
    cout<<pthread_name<<endl;
    return (void*)"Hunter";
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,pthread_hander,(void*)123);

    while(1)
    {
        cout<<"i am main pthread"<<getpid()<<endl;
        sleep(1);
    }

    void* ret;
    int i = pthread_join(tid,&ret);
    cout<<*(char*)ret<<endl;


    return 0;
}

