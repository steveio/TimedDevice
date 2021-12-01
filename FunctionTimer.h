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
#define TIMER_FUNCTION_EXP 0x11


typedef void (*pt2TimerFunction)(unsigned long * currEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts);
typedef void (*pt2TimerFunction)(unsigned long * currEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts, int pow, bool dir, unsigned long max, bool rev);

// default timer callback: recurring timer
void getNextEventIncremental(unsigned long * nextEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts)
{
  nextEvent = ts + interval;
}

// exponential timer incremental/decremental starting at interval upto zero / limit (max) with option to ping-pong
int expow_pow = 2;
bool expow_dir = 0;
unsigned long expow_max = SECS_PER_MIN * 5;
bool expow_rev = 0;

void getNextEventExPow(unsigned long * nextEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts, int _pow, bool _dir, unsigned long _max, bool _rev)
{
  if (prevEvent > 0)
  {
    unsigned long diff = ts - prevEvent;
    if (_dir = 0)
    {
      if (diff <= _max)
      {
        nextEvent = ts + (diff * _pow);
      } else if (_rev = 1) {
        expow_dir = 1;
        nextEvent = ts;
      }
    } else {
      if (diff / _pow > 1000)
      {
        nextEvent = ts - (diff / _pow);
      } else {
        expow_dir = 0;
        nextEvent = ts;
      }
    }
  } else {
    nextEvent = ts + interval;
  }
}

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
