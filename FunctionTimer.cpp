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
  if (_type == TIMER_FUNCTION)
  {
    if(_timerDefaultFunc)
    {
      (*_timerDefaultFunc)(&_nextEvent, _prevEvent, _interval, ts);
    }
  } else if (_type == TIMER_FUNCTION_EXP)
  {
    if(_timerExpFunc)
    {
      (*_timerExpFunc)(&_nextEvent, _prevEvent, _interval, ts, timer_expow_pow, timer_expow_dir, timer_expow_max, timer_expow_rev);
    }
  } else if (_type == TIMER_FUNCTION_RAND)
  {
    if(_timerRandFunc)
    {
      (*_timerRandFunc)(&_nextEvent, _prevEvent, ts, timer_rand_lower, timer_rand_upper);
    }

  }
}
