/**

RecurringTimer.h

Timer for recurring events at specific (hours|times) with interval n milliseconds

Solves problem of timer occuring every other (or every n) day(s),
  -- for example a pump should run (at specific times) every 3 days

*/

#ifndef RECURRINGTIMER_H_
#define RECURRINGTIMER_H_

#include <Timer.h>


#define TIMER_MILLIS_RECURRING 0x08


class RecurringTimer: public Timer
{

public:

  RecurringTimer();
  void init(int t, unsigned long ts, struct tmElementArray_t * fromTime, unsigned long interval, unsigned long duration);
  bool isScheduled(int h, unsigned long ts);

  protected:
    unsigned long  _interval; // timer interval (millisecs)
    unsigned long  _duration; // duration of timer event (millisecs)
    unsigned long  _nextEvent; // next timer event timestamp

  private:
    void _getNextEvent(unsigned long ts, unsigned long interval);

};


#endif;
