/**

RecurringTimer.h

Implements timer:
  events at specific (hours|times) with interval every n millis (millsis, secs, mins, hours, days)

*/

#ifndef RECURRINGTIMER_H_
#define RECURRINGTIMER_H_

#include <Timer.h>


#define TIMER_MILLIS_RECURRING 0x08


class RecurringTimer: public Timer
{

public:

  RecurringTimer();
  void init(int t, long * h, unsigned long timerInterval,  unsigned long eventDuration, unsigned long ts);
  bool isScheduled(int h, unsigned long ts);

  private:
    void _getNextEvent(unsigned long ts, unsigned long interval);

  protected:
    unsigned long  _timerInterval; // timer interval (milliseconds)
    unsigned long  _eventDuration; // timestamp next event begin
    unsigned long  _nextEvent; // timestamp next event begin
};


#endif;
