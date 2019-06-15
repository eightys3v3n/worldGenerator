#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

#define QUEUE_OWNED 0
#define QUEUE_UNLOCKED 1
#define QUEUE_NOT_OWNED 2

template<typename TYPE>
class Queue
{
public:
  void push(TYPE n); // adds a new last element, notifying all waiting threads.
  void pop(); // removes the first element.
  TYPE front(); // returns a reference to the first element.
  TYPE first(); // returns and removes the first element, notifying all threads.

  void clear(); // clears the queue.
  bool empty();

  unsigned int size(); // returns the size of the queue.
  void untilSize( unsigned int s ); // blocks until size is s.

  bool contains(TYPE e); // true if the Queue already contains e, false otherwise.

  void lock();
  bool unlock();

private:
  std::vector<TYPE> q; // the queue.
  std::condition_variable cv; // notified on queue modification.
  std::mutex m; // modification to queue contents.
  std::thread::id id; // keeps track of who locks the persistant lock.
};

template<typename TYPE>
void Queue<TYPE>::push(TYPE nu)
{
  std::unique_lock<std::mutex> lk(m);

  q.push_back(nu);

  lk.unlock();
  cv.notify_all();
}

template<typename TYPE>
TYPE Queue<TYPE>::front()
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
  q.erase(q.begin());

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

  q.erase(q.begin());

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
    q.erase(q.begin());

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

template<typename TYPE>
bool Queue<TYPE>::contains(TYPE e)
{
  for(auto v: q) {
    if (e == v)
      return true;
  }
  return false;
}

// lock the queue to this thread.
// returns:
//    true if it is already locked by someone else,
//    false if locked successfully or already locked by self.
template<typename TYPE>
void Queue<TYPE>::lock()
{
  m.lock();

  id = std::this_thread::get_id();
}

// unlockes the queue if this thread owns it.
// returns:
//    true if this thread doesn't own it,
//    false if it was successfully unlocked or it was already unlocked.
template<typename TYPE>
bool Queue<TYPE>::unlock()
{
  if ( ! m.try_lock() )
    return false;

  if ( id != std::this_thread::get_id() )
    return true;

  m.unlock();
  cv.notify_all();

  return false;
}
