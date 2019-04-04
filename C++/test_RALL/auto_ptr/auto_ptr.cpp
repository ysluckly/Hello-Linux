#include <iostream>

template<class T>
class AutoPtr
{
public:
  AutoPtr(T* ptr_)
    : ptr(ptr_)
  {
  }

  ~AutoPtr()
  {
    if(ptr)
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

  AutoPtr(AutoPtr<T>& t)
    : ptr(t.ptr)
  {
    std::cout << "拷贝构造!" << std::endl;
    t.ptr = NULL;
  }

  T& operator=( AutoPtr<T>& t)
  {
    std::cout << "赋值运算符重载!" << std::endl;
    if (this != &t)
    {
      if (ptr)
      {
        delete ptr;
      }

      ptr = t.ptr;
      t.ptr = NULL;
    }

    return *this;
  }

private:
  T* ptr;
};

struct Date
{
  int year;
  int month;
  int day;
};

int main()
{
  AutoPtr<Date> d(new Date);
  d->year = 20;
  AutoPtr<Date> d1 = d;
  //管理权转移
  if (d.operator->() == NULL)
  {
    std::cout << "null" << std::endl;
  }
  return 0;
}
