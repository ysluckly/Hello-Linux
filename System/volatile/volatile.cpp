//在其他的进程中已经改变了该变量的值，但是对于该进程来说还以为
//该变量的值没有发生改变所以会依旧到寄存器中读取该变量的值，这样的话就会发生错误
//这就是编译器的优化

#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

volatile int flag = 0;

void handler(int signo)
{
  flag = 1;
  cout << "change flag to 1" <<  endl;
}


int main()
{
  signal(SIGINT, handler);
  while (!flag)
  {
  }

  cout << "proc done..."<<flag << endl;
  return 0;
}
