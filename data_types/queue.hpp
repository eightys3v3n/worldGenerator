#ifndef QUEUE_TYPE
#define QUEUE_TYPE

#include <mutex>
#include <condition_variable>
#include <queue>

template<class TYPE>
class Queue
{
public:
  void push(TYPE n);
  TYPE& front();
  void pop();

  unsigned int size();
  bool empty();

private:
  std::queue<TYPE> q;
  std::condition_variable cv;
  std::mutex m;
};

#endif // QUEUE_TYPE