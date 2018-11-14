#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
void* pthread_hander(void* arg)
{

    const char* pthread_name =(char*)arg;

    sleep(1);
    cout<<pthread_name<<endl;
    return (void*)333;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,pthread_hander,(void*)123);

    while(1)
    {

     
        cout<<"i am main pthread"<<getpid()<<endl;
        sleep(2);
       }

    void* ret;
    pthread_join(tid,&ret);
    cout<<*(char*)ret<<endl;


    return 0;
}

