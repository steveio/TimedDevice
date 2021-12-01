/**

FunctionTimer.h

Time events to occur based on function()

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef FUNCTIONTIMER_H_
#define FUNCTIONTIMER_H_

#include <Arduino.h>
#include <Timer.h>


#define TIMER_FUNCTION 0x10


typedef void (*pt2TimerFunction)(unsigned long * currEvent, unsigned long * prevEvent, unsigned long * interval);


class FunctionTimer: public Timer
{

public:

  FunctionTimer();
  void init(int t, unsigned long ts, unsigned long interval);

  void setTimerCallback(pt2TimerFunction ptCallback)
  {
    this->_timerCallback = ptCallback;
  }

  unsigned long getNextEvent();

  protected:

  private:
    void _setNextEvent(unsigned long ts);
    pt2Function _timerCallback = NULL;
};


#endif
