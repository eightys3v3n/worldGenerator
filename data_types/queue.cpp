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
  void push(TYPE n); // adds a new last element.
  void pop(); // removes the first element.
  TYPE& front(); // returns a reference to the first element.
  TYPE first(); // returns and removes the first element.

  unsigned int size(); // returns the size of the queue.
  void clear(); // clears the queue.
  bool empty();
  void untilSize( unsigned int s ); // blocks until size is s.

private:
  std::queue<TYPE> q; // the queue.
  std::condition_variable cv; // notified on queue modification.
  std::mutex m; // modification to queue contents.
};

template<typename TYPE>
void Queue<TYPE>::push(TYPE nu)
{
  std::unique_lock<std::mutex> lk(m);

  q.push(nu);

  lk.unlock();
  cv.notify_all();
}

template<typename TYPE>
TYPE& Queue<TYPE>::front()
{
  TYPE buf;
  std::unique_lock<std::mutex> lk(m);

  while( q.empty() )
    cv.wait(lk);

  buf = q.front();

  lk.unlock();

  return buf;
}

template<typename TYPE>
void Queue<TYPE>::pop()
{
  std::unique_lock<std::mutex> lk(m);

  if ( ! q.empty() )
  q.pop();

  lk.unlock();
  cv.notify_all();
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

  cv.notify_all();

  return buf;
}

template<typename TYPE>
unsigned int Queue<TYPE>::size()
{
  return q.size();
}

template<typename TYPE>
void Queue<TYPE>::clear()
{
  std::unique_lock<std::mutex> lk(m);

  while ( ! q.empty() )
    q.pop();

  lk.unlock();

  cv.notify_all();
}

template<typename TYPE>
bool Queue<TYPE>::empty()
{
  return q.empty();
}

template<typename TYPE>
void Queue<TYPE>::untilSize( unsigned int s )
{
  std::mutex t;
  std::unique_lock<std::mutex> lk(t);

  while ( q.size() != s )
    cv.wait(lk);

  lk.unlock();
}
