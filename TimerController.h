/**

TimerController.h

Executor class for a cluster of timer instances

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

public:

  TimerController();
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
