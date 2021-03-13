
#include "Timer.h"


Timer::Timer() {}

// timer hour of day
void Timer::init(int t, long * h)
{
  _type = t;

  _timerHour = h;
}

// timer day of week / month
void Timer::init(int t, long * h, long * d)
{
  _type = t;

  _timerHour = h;
  switch(_type)
	{
		case TIMER_DAY_OF_WEEK:
      _timerDayOfWeek = d;
  		break;
		case TIMER_DAY_OF_MONTH:
      _timerDayOfMonth = d;
			break;
	}
}

void Timer::init(int t, struct tmElementArray_t * timeArray)
{
  _type = t;
  _timeArray = timeArray;
}


bool Timer::isScheduled(int h)
{
  bool status;
  status = _checkBitSet(h, _timerHour);
  if (!status) return false;

  return true;
}

/*
 * Is timer scheduled on for given Hour of Day and Day or Week or Day of Month
*/
bool Timer::isScheduled(int h, int d)
{
  bool status;
  switch(_type)
	{
		case TIMER_DAY_OF_WEEK:
      status = _checkBitSet(d, _timerDayOfWeek);
      if (!status) return false;
  		break;
		case TIMER_DAY_OF_MONTH:
      status = _checkBitSet(d, _timerDayOfMonth);
      if (!status) return false;
			break;
	}

  status = _checkBitSet(h, _timerHour);
  if (!status) return false;

  return true;
}

/*
 * Check minute timer
*/
bool Timer::isScheduled(int m, int h, int d)
{
    return _checkTimer(m,h,d);
}

/*
 * Check timestamp with timer array (on/off times)
 */
bool Timer::isScheduled(unsigned long ts)
{
    // first check day (d) with timer Day of Week bitmap

    int weekday = ((ts + 4) % 7) + 1;
    bool status;
    {
      return false;
    }

    // compute elapsed secs from previous midnight
    unsigned long elapsedTime = ts % SECS_PER_DAY;

    return _checkTimeArray(elapsedTime);
}


bool Timer::_checkTimer(int m, int h, int d)
{

  // first check day (d) with timer Day of Week bitmap
  bool status;
  long * p = &_timeArray->Wday;
  status = _checkBitSet(d, p);
  if (!status)
  {
    return false;
  }

  // convert times to elapsed secs
  unsigned long s1, s2, elapsedTime;
  s1 = m * SECS_PER_MIN;
  s2 = h * SECS_PER_HOUR;
  elapsedTime = s1+s2;

  return _checkTimeArray(elapsedTime);
}

bool Timer::_checkTimeArray(unsigned long ts)
{
  unsigned long s1, s2, onTime, offTime;

  // check each timeArray on/off pair
  for (int i = 0; i < _timeArray->n; i++)
  {
    s1 = _timeArray->onTime[i].Min * SECS_PER_MIN;
    s2 = _timeArray->onTime[i].Hour * SECS_PER_HOUR;
    onTime = s1 + s2;
    s1 = _timeArray->offTime[i].Min * SECS_PER_MIN;
    s2 = _timeArray->offTime[i].Hour * SECS_PER_HOUR;
    offTime = s1 + s2;

    if (ts >= onTime && ts <= offTime)
    {
      return true;
    }
  }

  return false;
}

// @todo
void Timer::_setBit(int n)
{
  switch(_type)
	{
		case TIMER_HOUR_OF_DAY:
			break;
		case TIMER_DAY_OF_WEEK:
			break;
		case TIMER_DAY_OF_MONTH:
			break;
	}

}

// Timer bitmask - check if bit at pos n is set in 32bit long l
bool Timer::_checkBitSet(int n, long * l)
{
  bool b = (*l >> (long) n) & 1U;
  return b;
}

// return hour of next timer on/off event from hour h
int Timer::getNextEvent(int h)
{
  long * l = _timerHour;

  bool c = _checkBitSet(h, l);

  for(int i=h+1; i<24; i++)
  {
    bool n = _checkBitSet(i, l);
    if (n != c)
    {
      return i;
    }
  }
  for(int i=0; i<=h; i++)
  {
    bool n = _checkBitSet(i, l);
    if (n != c)
    {
      return i;
    }
  }
}


void Timer::printSchedule(Stream &s)
{

  switch(_type)
	{
		case TIMER_DAY_OF_WEEK:
      s.println(F("Day of Week (0 Sun - 6 Sat): "));
      for(int i=0; i<7; i++)
      {
        bool isSet = _checkBitSet(i, _timerDayOfWeek);
        s.print(i);
        s.print(F("\t"));
        s.println(isSet);
      }
  		break;
		case TIMER_DAY_OF_MONTH:
      s.println(F("Day of Month (0 - 31): "));
      for(int i=0; i<32; i++)
      {
        bool isSet = _checkBitSet(i, _timerDayOfMonth);
        s.print(i);
        s.print(F("\t"));
        s.println(isSet);
      }
			break;
	}

  s.println(F("Hour Timer: "));
  for(int i=0; i<24; i++)
  {
    bool isSet = _checkBitSet(i, _timerHour);
    s.print(i);
    s.print(F("\t"));
    s.println(isSet);
  }

}
