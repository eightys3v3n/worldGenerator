#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <condition_variable>

template<typename TYPE>
class Vector
{
public:
  TYPE& operator[](unsigned int p);
  TYPE& at(int p);
  void push_back(TYPE n);
  bool contains(TYPE m);
  void clear(); // clears the queue.
  bool empty();

  unsigned int size(); // returns the size of the queue.
  void untilSize( unsigned int s ); // blocks until size is s.

  void lock();
  bool unlock();

private:
  std::vector<TYPE> v; // the queue.
  std::condition_variable cv; // notified on queue modification.
  std::mutex m; // modification to queue contents.
  std::thread::id id; // keeps track of who locks the persistant lock.
};


template<typename TYPE>
TYPE& Vector<TYPE>::operator[](unsigned int p)
{
  std::unique_lock<std::mutex> lk(m);

  TYPE& r = v[p];

  lk.unlock();
  cv.notify_all();

  return r;
}

template<typename TYPE>
TYPE& Vector<TYPE>::at(int p)
{
  std::unique_lock<std::mutex> lk(m);

  TYPE& r = v.at(p);

  lk.unlock();
  cv.notify_all();

  return r;
}

template<typename TYPE>
void Vector<TYPE>::push_back(TYPE n)
{
  std::unique_lock<std::mutex> lk(m);

  v.push_back(n);

  lk.unlock();
  cv.notify_all();
}

template<typename TYPE>
bool Vector<TYPE>::contains(TYPE m)
{
  for ( auto& e : v)
    if ( e == m )
      return true;

  return false;
}

template<typename TYPE>
unsigned int Vector<TYPE>::size()
{
  return v.size();
}

template<typename TYPE>
void Vector<TYPE>::clear()
{
  std::unique_lock<std::mutex> lk(m);

  v.clear();

  lk.unlock();
  cv.notify_all();
}

template<typename TYPE>
bool Vector<TYPE>::empty()
{
  return v.empty();
}

template<typename TYPE>
void Vector<TYPE>::untilSize( unsigned int s )
{
  std::mutex t;
  std::unique_lock<std::mutex> lk(t);

  while ( v.size() != s )
    cv.wait(lk);

  lk.unlock();
}

// lock the queue to this thread.
// returns:
//    true if it is already locked by someone else,
//    false if locked successfully or already locked by self.
template<typename TYPE>
void Vector<TYPE>::lock()
{
  m.lock();

  id = std::this_thread::get_id();
}

// unlockes the queue if this thread owns it.
// returns:
//    true if this thread doesn't own it,
//    false if it was successfully unlocked or it was already unlocked.
template<typename TYPE>
bool Vector<TYPE>::unlock()
{
  if ( ! m.try_lock() )
    return false;

  if ( id != std::this_thread::get_id() )
    return true;

  m.unlock();
  cv.notify_all();

  return false;
}