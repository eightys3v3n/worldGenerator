#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename TYPE>
class Queue
{
public:
  void push(TYPE n);
  TYPE& front();
  void pop();
  TYPE first();

  unsigned int size();
  bool empty();
  void clear();

private:
  std::queue<TYPE> q;
  std::condition_variable cv;
  std::mutex m;
};

template<typename TYPE>
void Queue<TYPE>::push(TYPE n)
{
  std::unique_lock<std::mutex> lk(m);

  q.push(n);

  lk.unlock();
  cv.notify_one();
}

template<typename TYPE>
TYPE& Queue<TYPE>::front()
{
  std::unique_lock<std::mutex> lk(m);

  while( q.empty() )
    cv.wait(lk);

  return q.front();
}

template<typename TYPE>
void Queue<TYPE>::pop()
{
  std::unique_lock<std::mutex> lk(m);

  while ( q.empty() )
    cv.wait(lk);

  q.pop();

  lk.unlock();
}

template<typename TYPE>
TYPE Queue<TYPE>::first()
{
  TYPE buf;
  std::unique_lock<std::mutex> lk(m);

  while ( q.empty() )
    cv.wait(lk);

  buf = q.front();
  q.pop();

  lk.unlock();

  return buf;
}

template<typename TYPE>
unsigned int Queue<TYPE>::size()
{
  return q.size();
}

template<typename TYPE>
bool Queue<TYPE>::empty()
{
  return q.empty();
}

template<typename TYPE>
void Queue<TYPE>::clear()
{
  while ( ! q.empty() )
    q.pop();
}