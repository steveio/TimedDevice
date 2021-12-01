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


class FunctionTimer: public Timer
{

public:

  FunctionTimer();
  void init();
  bool update(unsigned long ts);
  unsigned long getNextEvent();

  protected:

  private:
    void _setNextEvent(unsigned long ts);

};


#endif
