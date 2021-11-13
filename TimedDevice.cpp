/**

TimedDevice.cpp

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards


**/

#include "TimedDevice.h"

using namespace std;

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
void TimedDevice::on(unsigned long ts) {}
void TimedDevice::off(unsigned long ts) {}

// activate/deactivate scheduled device
void TimedDevice::update(unsigned long ts)
{
	_millis = ts;
	bool isScheduled = false;

	if (timer.getType() == TIMER_MINUTE) // Time based schedule
	{
		isScheduled = timer.isScheduled(ts);
	} else { // Bitmask schedule
		int h = timer.getHourGMTFromTS(ts);
	  int d = timer.getDayOfWeekFromTS(ts);
		isScheduled = timer.isScheduled(h,d);
	}

	/*
	serial->println(isScheduled);
	serial->print(_millis);
	serial->print("\t");
	serial->print(_lastActivation);
	serial->print("\t");
	serial->print(_delay);
	serial->print("\t");
	serial->println(_duration);
	*/


	if (isScheduled)
  {
		activate();
  } else {
		deactivate();
	}
}

bool TimedDevice::activate()
{
	if(!_active && (_lastActivation == 0 || (_millis >= _lastActivation + floor(_delay / 1000))))
  {
    on(_millis);
		return true;
  }
}

bool TimedDevice::deactivate()
{
  if (_active && (_millis >= _lastActivation + floor(_duration / 1000)))
  {
    off(_millis);
		return true;
  }
}

long TimedDevice::getActivations()
{
	return _activations;
}

unsigned long TimedDevice::getLastActivation()
{
	return _lastActivation;
}

unsigned long TimedDevice::getLastDeActivation()
{
	return _lastDeActivation;
}
