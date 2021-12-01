/**

FunctionTimer.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

**/


#include "Timer.h"
#include "FunctionTimer.h"


FunctionTimer::FunctionTimer() {}

void FunctionTimer::init(int t, unsigned long ts, unsigned long interval)
{

  _type = t;
  _startTs = ts;
  _interval = interval;

  // compute timer next event + timeout
  _setNextEvent(_startTs);
}


void FunctionTimer::_setNextEvent(unsigned long ts)
{
  _prevEvent = ts;
  if(_timerCallback)
  {
    call(_timerCallback(&_nextEvent, &_prevEvent, &_interval));
  }
}
