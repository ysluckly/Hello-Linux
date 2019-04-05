#include <iostream>

template<class T>
class SmartPtr
{
public:
  SmartPtr(T* ptr_)
    : ptr(ptr_)
  {
  }

  ~SmartPtr()
  {
    if (ptr)
    {
      delete ptr;
    }
  }

  T& operator*()
  {
    return *ptr;
  }

  T* operator->()
  {
    return ptr;
  }
  
private:
  T* ptr;
};

struct Date
{
  int year;
  int month;
  int date;
};

int main()
{
  SmartPtr<Date> d(new Date);//拷贝构造
  d->year = 1;
  d->month = 2;
  d->date = 3;
  std::cout << d->year << d->month << d->date << std::endl;

  SmartPtr<int> i(new int);
  *i = 10;
  std::cout << *i << std::endl;
  return 0;
}
