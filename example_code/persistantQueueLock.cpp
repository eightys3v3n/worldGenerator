#include <iostream>
#include <thread>
#include <chrono>
#include "../data_types/queue.hpp"
using namespace std;
using namespace chrono;

mutex m;
bool running = true;

void thf( Queue<int>* qu )
{
  while ( running )
  {
    qu->push(1);
    cout << "thread added number" << endl;

    this_thread::sleep_for( milliseconds(300) );
  }
}

int main()
{
  Queue<int> qu;

  thread th( thf, &qu );

  this_thread::sleep_for( milliseconds(1000) );

  qu.lock();
  cout << "main locked" << endl;
  this_thread::sleep_for( seconds(2) );
  qu.unlock();
  cout << "main unlocked" << endl;

  this_thread::sleep_for( milliseconds(1400) );

  running = false;
  th.join();

  return false;
}