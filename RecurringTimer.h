/**

RecurringTimer.h

Timer for recurring events starting from HH:MM:SS with interval (period) n milliseconds

Solves problem of timer occuring every other (or every n) day(s),
  -- for example a sprinkler should run (at specific times) every 3 days

A stable timesource (for example an RTC) should be used for accuracy

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

*/

#ifndef RECURRINGTIMER_H_
#define RECURRINGTIMER_H_

#include <Timer.h>


#define TIMER_MILLIS_RECURRING 0x08


class RecurringTimer: public Timer
{

public:

  RecurringTimer();
  void init(int t, struct tmElementArray_t * startTime, unsigned long interval);
  bool update(unsigned long ts);

  protected:
    unsigned long  _startTs;      // timer from timestamp
    unsigned long  _nextEvent;    // next event timestamp

    unsigned long  _interval = 0;     // interval (millisecs)
    int _activations = 1;         // default no activations per cycle

  private:
    void _getNextEvent(unsigned long ts, unsigned long interval);

};


#endif;
