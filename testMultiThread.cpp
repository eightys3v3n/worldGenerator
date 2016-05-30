#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;
using namespace chrono;

mutex m;
bool running = true;
condition_variable cv;

class Queue
{
public:
  void push(int new)
  {
    unique_lock<mutex> lk(m);
    //cout << "push:locked" << endl;
    q.push(new);
    //cout << "push:pushed" << endl;
    lk.unlock();
    //cout << "push:unlocked" << endl;
    cv.notify_one();
  }

  int pop()
  {
    unique_lock<mutex> lk(m);
    //cout << "pop:locked" << endl;
    //cout << "pop:waiting for elements" << endl;
    while ( q.empty() )
      cv.wait(lk);
    //cout << "pop:elements exist" << endl;

    int buf = q.front();
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
  queue<int> q;
};


Queue<int> qq;


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
      cout << "pop" << id << ":" << qq.pop() << endl;
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