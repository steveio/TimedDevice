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

// activate/deactivate device with bitmap hour schedule
void TimedDevice::update(int h, int d, unsigned long ts)
{
	_millis = ts;

	if (timer.isScheduled(h,d))
  {
		activate();
  } else {
		deactivate();
	}

}

// activate/deactivate device with point in time schedule
void TimedDevice::update(unsigned long ts)
{
	_millis = ts;

	if (!timer.isScheduled(ts))
  {
		deactivate();
  } else {
		activate();
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
