#include <iostream>
#include <mutex>
#include <thread>

template<class Mutex>
class LockGuard
{
public:
  LockGuard(Mutex& mutex)
    : _mutex(mutex)
  {
    _mutex.lock();
  }

  ~LockGuard()
  {
    _mutex.unlock();
  }

  LockGuard(const LockGuard& lg) = delete;
  LockGuard& operator=(const LockGuard& lg) = delete;

private:
  Mutex& _mutex;
};

std::mutex _mutex;
int n = 0;

void Func()
{
  for (int i = 0; i < 100000000; i++)
  {
    LockGuard<std::mutex> mu(_mutex);
    n++;
  }
}

int main()
{
  int begin = clock();
  std::thread t1(Func);
  std::thread t2(Func);

  t1.join();
  t2.join();

  int end = clock();
  std::cout << "n: " << n << std::endl;
  std::cout << "end - begin time: " << end - begin << std::endl;
  return 0;
}
