/**

RecurringTimer.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards

**/


#include "Timer.h"
#include "RecurringTimer.h"

#include <stdio.h>


RecurringTimer::RecurringTimer() {}

// start timer from now (current ts)
void RecurringTimer::init(int t, unsigned long ts, unsigned long interval, unsigned long duration)
{

  _type = t;
  _interval = interval / 1000;
  _startTs = ts;
  _duration = duration / 1000;

  // compute timer next event + timeout
  _setNextEvent(_startTs);
  _setTimeout(_startTs);
}


// start timer from specific point in time (specified as HH:MM::SS relative to current ts)
void RecurringTimer::init(int t, unsigned long ts, struct tmElements_t * startTime, unsigned long interval)
{

  _type = t;
  _interval = interval / 1000;

  // convert from time HH:MM:SS to timestamp relative to startTime
  unsigned long s1, s2, s3, eventTs;

  s1 = startTime->Sec;
  s2 = startTime->Min * SECS_PER_MIN;
  s3 = startTime->Hour * SECS_PER_HOUR;

  eventTs = s1 + s2 + s3;

  // compute start timestamp
  unsigned long elapsedTs = ts - (ts % SECS_PER_DAY);

  if (eventTs + elapsedTs < ts)  // start time has passed
  {
    _startTs = eventTs + elapsedTs + SECS_PER_DAY;
  } else {
    _startTs = eventTs + elapsedTs;
  }

  // compute timer next event
  _setNextEvent(_startTs);

  //printf("startTs: ");
  //printf("%lu\n",_startTs);

  //printf("nextEventTs: ");
  //printf("%lu\n",_nextEvent);

}

bool RecurringTimer::update(unsigned long ts)
{

  if (ts >= _nextEvent)
  {
    _setNextEvent(ts);
    _setTimeout(ts);

    if (_duration > 0)
    {
      _active = true;
    }
    _lastActivation = ts;;

    if (_activations-- > 0)
    {
      if (_callbackArr[CALLBACK_TIMER_ACTIVE])
      {
        call(CALLBACK_TIMER_ACTIVE);
      }
      _activations = TIMER_DEFAULT_ACTIVATIONS;
    }
  }

  // check active duration timeout
  if (_duration > 0 && _lastActivation > 0 && _active == true && ts > _timeout)
  {
    _active = false;
    _lastDeActivation = ts;
    if (_callbackArr[CALLBACK_TIMER_TIMEOUT])
    {
      call(CALLBACK_TIMER_TIMEOUT);
    }
  }

  return false;
}

unsigned long RecurringTimer::getNextEvent()
{
  return _nextEvent;
}

unsigned long RecurringTimer::getInterval()
{
  return _interval;
}

void RecurringTimer::_setNextEvent(unsigned long ts)
{
  _nextEvent = ts + _interval;
}

void RecurringTimer::_setTimeout(unsigned long ts)
{
  _timeout = ts + _duration;
}

unsigned long RecurringTimer::getTimeout()
{
  return _timeout;
}
