#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "types.hpp"

// struct Queue
{
  void Queue::add( int n )
  {
    unique_lock<mutex> lk(m);

    q.push(n);

    lk.unlock();
    cv.notify_one(); // to notify any waiting calls to pop()
  }

  int Queue::pop()
  {
    unique_lock<mutex> lk(m);

    // if there are no elements, wait for one
    while ( q.empty() )
      cv.wait(lk);

    // read the next element and remove it fron the queue
    int buf = q.front();
    q.pop();

    lk.unlock();
    return buf;
  }

  bool Queue::empty()
  {
    return q.empty();
  }
}