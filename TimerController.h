/**

TimerController.h

Executor class for a collection of 1..n timer instances

Timers are registered with TimerController .add()
In loop TimerContoller.update() is called executing any pending timer events.

One-shot timers are removed on activation.

Maintains internally a sorted linked list timer data structure.

Manage n Timer instances efficiently, support multicore / thread architecture where available

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef TIMERCONTROLLER_H_
#define TIMERCONTROLLER_H_


#include <TimerController.h>
#include <MergeSortLinkedList.h>


class TimerController
{

  TimerController(){};

  public:
    static TimerController& getInstance()
    {
      static TimerController instance;
      return instance;
    };
    void add(Timer t);
    bool update(unsigned long ts);

  protected:
    Node* _node = NULL;
  	MergeSort _mergeSort;


  private:

};


#endif
