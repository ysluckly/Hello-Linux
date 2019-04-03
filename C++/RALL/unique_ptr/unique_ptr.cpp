#include <iostream>

template<class T>
class UniquePtr
{
public:
  UniquePtr(T* ptr)
    : _ptr(ptr)
  {
  }

  ~UniquePtr()
  {
    if (_ptr)
    {
      delete _ptr;
    }
  }

  T& operator*()
  {
    return *_ptr;
  }

  T* operator->()
  {
    return _ptr;
  }

private:
  //C++98 
  UniquePtr(UniquePtr& t);
  T& operator=(UniquePtr& t);

  //C++11
  //UniquePtr(UniquePtr& t) = delete;
  //T& operator=(UniquePtr& t) = delete;
 
private:
  T* _ptr;
};

struct Date
{
  int year;
  int month;
  int day;
  friend std::ostream& operator<< (std::ostream& cout,const Date& d)
  {
    cout << d.year << "-" << d.month << "-" << d.day << std::endl;
    return cout;
  }
};

int main()
{
  UniquePtr<Date> d(new Date());
  d->year = 1;
  d->month = 2;
  d->day = 3;
  std::cout << *d;
  //UniquePtr<Date> d1 = d;
  return 0;
}
