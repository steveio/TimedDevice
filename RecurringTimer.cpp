

#include "Timer.h"
#include "RecurringTimer.h"
#include "TimedDevice.h"


RecurringTimer::RecurringTimer() {}


void RecurringTimer::init(int t, long * h, unsigned long timerInterval,  unsigned long eventDuration, unsigned long ts)
{

  _type = t;
  _timerHour = h;
  _timerInterval = timerInterval;
  _eventDuration = eventDuration;

  // convert fully qualified timestamp to elapsed secs from previous midnight
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  _getNextEvent(elapsedTime, 0);

}

bool RecurringTimer::isScheduled(int h, unsigned long ts)
{

  bool status = false;

  // convert fully qualified timestamp to elapsed secs from previous midnight
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  if (elapsedTime >= _nextEvent && elapsedTime <= _nextEvent + _eventDuration)
  {
    status = true;
  }

  status = _checkBitSet(h, _timerHour); // check hour timer


  if (ts > _nextEvent + _timerInterval)
  {
    _getNextEvent(elapsedTime, _timerInterval);
  }

  return status;
}

void RecurringTimer::_getNextEvent(unsigned long ts, unsigned long interval)
{
  unsigned long elapsedTime = ts % SECS_PER_DAY;

  _nextEvent = elapsedTime + interval;
}
