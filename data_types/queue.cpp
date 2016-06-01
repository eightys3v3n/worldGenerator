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
  void untilEmpty();

private:
  std::queue<TYPE> q; // the queue.
  std::condition_variable n; // used to wait for a new element in the queue.
  std::condition_variable o; // used to wait until the queue is empty.
  std::mutex newM; // used with n
  std::mutex oldM; // used with o
};

template<typename TYPE>
void Queue<TYPE>::push(TYPE n)
{
  std::unique_lock<std::mutex> lk(newM);

  q.push(n);

  lk.unlock();

  // notify front(), first(), pop() that a new element is available.
  n.notify_one();
}

template<typename TYPE>
TYPE& Queue<TYPE>::front()
{
  std::unique_lock<std::mutex> lk(newM);

  while( q.empty() )
    n.wait(lk);

  return q.front();
}

template<typename TYPE>
void Queue<TYPE>::pop()
{
  std::unique_lock<std::mutex> lk(newM);

  while ( q.empty() )
    n.wait(lk);

  q.pop();

  lk.unlock();
}

template<typename TYPE>
TYPE Queue<TYPE>::first()
{
  TYPE buf;
  std::unique_lock<std::mutex> lk(newM);

  while ( q.empty() )
    n.wait(lk);

  buf = q.front();
  q.pop();

  lk.unlock();

  // notify untilEmpty() that the queue is empty.
  if ( q.empty() )
    o.notify_one();

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
  unique_lock<std::mutex> lk(newM);

  while ( ! q.empty() )
    q.pop();

  lk.unlock();
}

template<typename TYPE>
void Queue<TYPE>::untilEmpty()
{
  unique_lock<std::mutex> lk(oldM);

  while ( ! q.empty() )
    o.wait(lk);
}
