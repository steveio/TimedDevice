
#include "RecurringTimer.h"

RecurringTimer::RecurringTimer() {}


void RecurringTimer::init(int t, unsigned long ts, struct tmElementArray_t * fromTime, unsigned long interval,  unsigned long duration)
{

  _type = t;
  _interval = interval;
  _duration = duration;

  // convert fully qualified timestamp to elapsed secs from previous midnight
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  _getNextEvent(elapsedTime, 0);

}

bool RecurringTimer::isScheduled(int h, unsigned long ts)
{

  bool status = false;

  // convert fully qualified timestamp to elapsed secs from previous midnight
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  if (elapsedTime >= _nextEvent && elapsedTime <= _nextEvent + _duration)
  {
    status = true;
  }

  status = _checkBitSet(h, _timerHour); // check hour timer


  if (ts > _nextEvent + _interval)
  {
    _getNextEvent(elapsedTime, _interval);
  }

  return status;
}

void RecurringTimer::_getNextEvent(unsigned long ts, unsigned long interval)
{
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  _nextEvent = elapsedTime + interval;
}
