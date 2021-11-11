
#include "RecurringTimer.h"

RecurringTimer::RecurringTimer() {}


void RecurringTimer::init(int t, unsigned long ts, struct tmElements_t * startTime, unsigned long interval)
{

  _type = t;
  _interval = interval;

  // convert from time HH:MM:SS to timestamp relative to startTime
  unsigned long s1, s2, s3, eventTs;

  s1 = startTime->Sec;
  s2 = startTime->Min * SECS_PER_MIN;
  s3 = startTime->Hour * SECS_PER_HOUR;

  eventTs = s1 + s2 + s3;

  // compute start timestamp
  unsigned long elapsedTs = ts % SECS_PER_DAY;

  if (eventTs + elapsedTs < ts)
  {
    _startTs = eventTs + elapsedTs + SECS_PER_DAY;
  } else {
    _startTs = eventTs + elapsedTs;
  }

  // compute timer next event
  _getNextEvent(_startTs, interval);

}

bool RecurringTimer::update(unsigned long ts)
{
  if (ts == _nextEvent)
  {
    _getNextEvent(_nextEvent, _interval);

    if (_activations-- > 0)
    {
      if (function_callback)
      {
        call();
      }
      return true;
    }
  }
}

void RecurringTimer::_getNextEvent(unsigned long ts, unsigned long interval)
{
  _nextEvent = ts + interval;
}
