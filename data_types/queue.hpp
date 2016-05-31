#ifndef CHUNK_
#define CHUNK_

#include <mutex>
#include <condition_variable>
#include <queue>

class Queue
{
public:
  void push(int new);
  int pop();
  bool empty();

private:
  queue<int> q;
  condition_variable cv;
  mutex m;
};

#endif // CHUNK_