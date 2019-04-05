#include <iostream>
#include <mutex>
#include <memory>

template<class T>
class SharedPtr
{
public:
  SharedPtr(T* ptr = nullptr)
    : _ptr(ptr)
    , _RefCount(new int(1))
    , _pMutex(new std::mutex)
  {
    if (_ptr == nullptr)
    {
      *_RefCount = 0;
    }
  }

  ~SharedPtr()
  {
    Release();
  }

  T* operator->()
  {
    return _ptr;
  }

  T& operator*()
  {
    return *_ptr;
  }

  SharedPtr(SharedPtr& sp)
    : _ptr(sp._ptr)
    , _RefCount(sp._RefCount)
    , _pMutex(sp._pMutex)
  {
    if (_ptr)
    {
      AddRefCount();
    }
  }

  SharedPtr& operator=(SharedPtr& sp)
  {
    //只需要判断是否管理的同一个对象
    if (_ptr != sp._ptr)
    {
      //释放对旧的对象的管理
      Release();

      //管理新的对象
      _ptr = sp._ptr;
      _pMutex = sp._pMutex;
      _RefCount = sp._RefCount;

      //只有当新的对象不是nullptr猜对其进行引用计数增加1
      if (_ptr)
      {
        AddRefCount();
      }
    }

    return *this;
  }

  int SubRefCount()
  {
    _pMutex->lock();
    (*_RefCount)--;
    _pMutex->unlock();

    return *_RefCount;
  }

  int AddRefCount()
  {
    _pMutex->lock();
    (*_RefCount)++;
    _pMutex->unlock();

    return *_RefCount;
  }

  T* Get()
  {
    return _ptr;
  }

  int& UseCount()
  {
    return *_RefCount;
  }

private:
  void Release()
  {
    if (_ptr && (SubRefCount() == 0))
    {
      delete _ptr;
      delete _RefCount;
      delete _pMutex;
    }
  }

private:
  T* _ptr;
  int*  _RefCount;
  std::mutex* _pMutex;
};

struct Date
{
  int year = 1;
  int month = 2;
  int day = 3;
  friend std::ostream& operator<< (std::ostream& cout,const Date& d)
  {
    cout << d.year << "-" << d.month << "-" << d.day << std::endl;
    return cout;
  }
};

//struct ListNode 
//{
//  int _data;
//  SharedPtr<ListNode> _prev;
//  SharedPtr<ListNode> _next;
//};

struct ListNode 
{
  int _data;
  std::weak_ptr<ListNode> _prev;
  std::weak_ptr<ListNode> _next;
};

template<class T>
struct Free
{
  void operator()(T* ptr)
  {
    std::cout << "free !" << std::endl;
    free(ptr);
  }
};

int main()
{
  Free<int> free;

  //不是new出来的对象通过智能指针管理，采用仿函数（定制删除器）
  std::shared_ptr<int> _int(new int(6));
  std::shared_ptr<int> _int1((int*)malloc(4), free);

  //对于循环引用的解决方法，对于结点指针使用weak_ptr
  //std::shared_ptr<ListNode> node1(new ListNode());
  //std::shared_ptr<ListNode> node2(new ListNode());
  //std::cout << node1.use_count() << std::endl;
  //std::cout << node2.use_count() << std::endl;

  //node1->_next = node2;
  //node1->_prev = node1;
  //std::cout << node1.use_count() << std::endl;
  //std::cout << node2.use_count() << std::endl;

  //测试循环引用
 // SharedPtr<ListNode> node1(new ListNode());
 // SharedPtr<ListNode> node2(new ListNode());
 // std::cout << node1.UseCount() << std::endl;
 // std::cout << node2.UseCount() << std::endl;

 // node1->_next = node2;
 // node1->_prev = node1;
 // std::cout << node1.UseCount() << std::endl;
 // std::cout << node2.UseCount() << std::endl;


  //测试引用计数是否正确
 // SharedPtr<int> sp1(new int(10));
 // SharedPtr<int> sp2(sp1);
 // *sp2 = 20;
 // std::cout << sp1.UseCount() << std::endl;
 // std::cout << sp2.UseCount() << std::endl;
 // SharedPtr<int> sp3(new int(10));
 // sp2 = sp3;
 // std::cout << sp1.UseCount() << std::endl;
 // std::cout << sp2.UseCount() << std::endl;
 // std::cout << sp3.UseCount() << std::endl;
 // sp1 = sp3;
 // std::cout << sp1.UseCount() << std::endl;
 // std::cout << sp2.UseCount() << std::endl;
 // std::cout << sp3.UseCount() << std::endl;
  //SharedPtr<Date> d(new Date());
  //SharedPtr<Date> d1(d);
  //std::cout << *d << std::endl;;
  //std::cout << *d << std::endl;;
  return 0;
}
