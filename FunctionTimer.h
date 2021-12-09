/**

FunctionTimer.h

Time events to occur where interval is based on function()

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef FUNCTIONTIMER_H_
#define FUNCTIONTIMER_H_

#include <Arduino.h>
#include <Timer.h>


#define TIMER_FUNCTION 0x10
#define TIMER_FUNCTION_EXP 0x11
#define TIMER_FUNCTION_RAND 0x12


typedef void (*pt2TimerDefaultFunction)(unsigned long * currEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts);
typedef void (*pt2TimerExpFunction)(unsigned long * currEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts, int pow, bool dir, unsigned long max, bool rev);
typedef void (*pt2TimerRandFunction)(unsigned long * currEvent, unsigned long prevEvent, unsigned long ts, unsigned long _upper, unsigned long _lower);

// default timer callback: recurring timer
void getNextEvent(unsigned long * nextEvent, unsigned long prevEvent, unsigned long interval, unsigned long ts)
{
  nextEvent = ts + interval;
}

// exponential timer incremental/decremental starting at interval upto zero / limit (max) with option to ping-pong
int timer_expow_pow = 2;
bool timer_expow_dir = 0;
unsigned long timer_expow_max = SECS_PER_MIN * 5;
bool timer_expow_rev = 0;

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
        timer_expow_dir = 1;
        nextEvent = ts;
      }
    } else {
      if (diff / _pow > 1000)
      {
        nextEvent = ts - (diff / _pow);
      } else {
        timer_expow_dir = 0;
        nextEvent = ts;
      }
    }
  } else {
    nextEvent = ts + interval;
  }
}

unsigned long timer_rand_lower = 1000;
unsigned long timer_rand_upper = 200000;


void getNextEventRand(unsigned long * nextEvent, unsigned long prevEvent, unsigned long ts, unsigned long _upper, unsigned long _lower)
{

  unsigned long interval = (rand() % (_upper - _lower + 1)) + _lower;
  nextEvent = ts + interval;
}


pt2TimerDefaultFunction timerDefaultFunc = &getNextEvent;
pt2TimerExpFunction timerExpFunc = &getNextEventExPow;
pt2TimerRandFunction timerRandFunc = &getNextEventRand;


class FunctionTimer: public Timer
{

public:

  FunctionTimer();
  void init(int t, unsigned long ts, unsigned long interval);

  void setTimerCallback(pt2TimerDefaultFunction ptCallback)
  {
    _timerDefaultFunc = ptCallback;
  };

  void setTimerCallback(pt2TimerExpFunction ptCallback)
  {
    _timerExpFunc = ptCallback;
  };

  void setTimerCallback(pt2TimerRandFunction ptCallback)
  {
    _timerRandFunc = ptCallback;
  };

  protected:

  private:
    void _setNextEvent(unsigned long ts);
    pt2TimerDefaultFunction _timerDefaultFunc = timerDefaultFunc;
    pt2TimerExpFunction _timerExpFunc = timerExpFunc;
    pt2TimerRandFunction _timerRandFunc = timerRandFunc;
};


#endif
