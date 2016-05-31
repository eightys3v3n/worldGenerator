#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "../data_types/queue.cpp"
using namespace std;
using namespace chrono;

bool running = true;
Queue<int> qq;
/*mutex m;
condition_variable cv;

template<typename TYPE>
class Queue
{
public:
  void push(TYPE n)
  {
    unique_lock<mutex> lk(m);
    //cout << "push:locked" << endl;
    q.push(n);
    //cout << "push:pushed" << endl;
    lk.unlock();
    //cout << "push:unlocked" << endl;
    cv.notify_one();
  }

  TYPE pop()
  {
    unique_lock<mutex> lk(m);
    //cout << "pop:locked" << endl;
    //cout << "pop:waiting for elements" << endl;
    while ( q.empty() )
      cv.wait(lk);
    //cout << "pop:elements exist" << endl;

    TYPE buf = q.front();
    //cout << "pop:got element " << buf << endl;
    q.pop();
    //cout << "pop:removed element" << endl;

    //cout << "pop:unlocked" << endl;
    lk.unlock();
    return buf;
  }

  bool empty()
  {
    return q.empty();
  }

private:
  queue<TYPE> q;
};*/


void produceF()
{
  for ( unsigned int i = 0; i < 20; i++ )
  {
    cout << "pushing " << i << endl;
    qq.push(i);
    this_thread::sleep_for( milliseconds(100) );
    //cout << "pushed input" << endl
  }

  running = false;
}

void consumeF(int id)
{
  while ( running )
  {
    while ( ! qq.empty() )
    {
      cout << "pop" << id << ":" << qq.front() << endl;
      qq.pop();
      this_thread::sleep_for( milliseconds(400) );
    }
  }
}

int main()
{
  cout << "starting consumer" << endl;
  thread consume( consumeF, 0 );
  thread consume1( consumeF, 1 );
  thread consume2( consumeF, 2 );
  thread consume3( consumeF, 3 );

  cout << "starting producer" << endl;
  thread produce( produceF );

  consume.join();
  consume1.join();
  consume2.join();
  consume3.join();
  produce.join();

  return false;
}