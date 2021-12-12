/**

TimerController.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

**/


#include "TimerController.h"
#include <stdlib.h>


void TimerController::add(Timer t)
{
  _mergeSort.push(&_node, t);
  _mergeSort.Sort(&_node);
}

// single thread implementation
bool TimerController::update(unsigned long ts)
{

  Node * head = _node;

  while (_node != NULL)
  {
    if (ts >= _node->timer.getNextEvent())
    {
      // execute timer update()
      _node->timer.update(ts);

      // if timer is one shot : remove node from linked list
      //Node * expiredNode = _node;
      //if (_node == NULL) break;
      //free(expiredNode);
    }

    _node = _node->next;
  }

  _node = head;

  _mergeSort.Sort(&_node);

  return false;
}
