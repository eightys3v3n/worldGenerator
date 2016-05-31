#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "queue.hpp"

template<typename TYPE> void Queue<TYPE>::push(TYPE n)
{
  std::unique_lock<std::mutex> lk(m);

  q.push(n);

  lk.unlock();
  cv.notify_one();
}

template<typename TYPE> TYPE& Queue<TYPE>::front()
{
  std::unique_lock<std::mutex> lk(m);

  while( q.empty() )
    cv.wait(lk);

  return q.front();
}

template<typename TYPE> void Queue<TYPE>::pop()
{
  std::unique_lock<std::mutex> lk(m);

  while ( q.empty() )
    cv.wait(lk);

  q.pop();

  lk.unlock();
}

template<typename TYPE> unsigned int Queue<TYPE>::size()
{
  return q.size();
}

template<typename TYPE> bool Queue<TYPE>::empty()
{
  return q.empty();
}