/**

TimedDevice.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards


**/

#include "TimedDevice.h"


TimedDevice::TimedDevice () {}

void TimedDevice::initTimer(Timer t)
{
	timer = t;
}

bool TimedDevice::isActive()
{
	return _active;
}

// extending classes implement on/off according to device hardware interface
void TimedDevice::on() {}
void TimedDevice::off() {}

// activate/deactivate scheduled device
void TimedDevice::update(unsigned long ts)
{
	_millis = ts;
	bool isActive = false;

	if (timer.getType() == TIMER_MINUTE) // Time based schedule
	{
		isActive = timer.isScheduled(ts);
	} else { // Bitmask schedule
		int h = timer.getHourGMTFromTS(ts);
	  int d = timer.getDayOfWeekFromTS(ts);
		isActive = timer.isScheduled(h,d);
	}

	if (isActive)
  {
		activate();
  } else {
		deactivate();
	}
}

bool TimedDevice::activate()
{
	if(!_active && (_lastActivation == 0 || (_millis > _lastActivation + _delay)))
  {
    on();
		return true;
  }
}

bool TimedDevice::deactivate()
{
  if (_active && (_millis > _lastActivation + _duration))
  {
    off();
		return true;
  }
}

long TimedDevice::getActivations()
{
	return _activations;
}
