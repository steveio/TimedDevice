/**

TimerController.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

**/


#include "TimerController.h"

#include <stdio.h>


TimerController::TimerController() {}


TimerController::add(Timer t)
{
  _mergeSort.push(&_node, t);
  _mergeSort.Sort(&_node);
}

// single thread implementation
TimerController::update(unsigned long ts)
{
  while (true)
  {
    if (ts >= _node->timer.getNextEvent())
    {
      // execute timer update()
      _node->timer.update(ts);
      // remove node from linked list
      Node* expiredNode = &_node;
      _node = _node->next;
      free(expiredNode);
    } else {
      break;
    }
  }
}
