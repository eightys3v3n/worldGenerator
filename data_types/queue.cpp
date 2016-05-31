#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "queue.hpp"

void Queue::push(int new)
{
  std::unique_lock<std::mutex> lk(m);

  q.push(new);

  lk.unlock();
  cv.notify_one();
}

int Queue::pop()
{
  std::unique_lock<std::mutex> lk(m);

  while ( q.empty() )
    cv.wait(lk);

  int buf = q.front();
  q.pop();

  lk.unlock();
  return buf;
}

bool Queue::empty()
{
  return q.empty();
}