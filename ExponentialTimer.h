/**

ExponentialTimer.h

Timer with incremental events based on exponential ratio

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef EXPONENTIALTIMER_H_
#define EXPONENTIALTIMER_H_

#include <Arduino.h>
#include <Timer.h>


#define TIMER_EXPONENTIAL 0x09


class ExponentialTimer: public Timer
{

public:

  ExponentialTimer();
  void init();
  bool update(unsigned long ts);
  unsigned long getNextEvent();

  protected:

  private:
    void _setNextEvent(unsigned long ts);

};


#endif
