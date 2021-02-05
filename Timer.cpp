
#include "Timer.h"


Timer::Timer() {}

void Timer::init(int t, long * h)
{
  _type = t;

  _timerHour = h;

  switch(_type)
	{
		case TIMER_DAY_OF_WEEK:
      //timerDayOfWeek = d;
  		break;
		case TIMER_DAY_OF_MONTH:
      //timerDayOfMonth = d;
			break;
	}
}

bool Timer::isScheduled(int h)
{
  bool status;
  status = checkBitSet(h, _timerHour);
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
      status = checkBitSet(d, _timerDayOfWeek);
      if (!status) return false;
  		break;
		case TIMER_DAY_OF_MONTH:
      status = checkBitSet(d, _timerDayOfMonth);
      if (!status) return false;
			break;
	}

  status = checkBitSet(h, _timerHour);
  if (!status) return false;

  return true;
}

// @todo
void Timer::setBit(int n)
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
bool Timer::checkBitSet(int n, long * l)
{
  bool b = (*l >> (long) n) & 1U;
  return b;
}

// return hour of next timer on/off event from hour h
int Timer::getNextEvent(int h)
{
  long * l = _timerHour;

  bool c = checkBitSet(h, l);

  for(int i=h+1; i<24; i++)
  {
    bool n = checkBitSet(i, l);
    if (n != c)
    {
      return i;
    }
  }
  for(int i=0; i<=h; i++)
  {
    bool n = checkBitSet(i, l);
    if (n != c)
    {
      return i;
    }
  }
}


void Timer::printSchedule(Stream &s)
{

  s.println("Hour Timer: ");
  for(int i=0; i<24; i++)
  {
    bool isSet = checkBitSet(i, _timerHour);
    s.print(i);
    s.print("\t");
    s.println(isSet);
  }

}
