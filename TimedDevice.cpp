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

// toggle device on/off
void TimedDevice::toggle()
{
  if (!_active)
  {
    on();
  } else {
    off();
  }
}

// extending classes implement on/off according to device hardware interface
void TimedDevice::on() {}

void TimedDevice::off() {}

// activate/deactivate device according to timer schedule, w/ duration & interval (delay)
void TimedDevice::activate(int h)
{
  bool isScheduled = timer.isScheduled(h);

  if (!isScheduled)
  {
    return;
  }

  if(!_active && (_lastActivation == 0 || (millis() > _lastActivation + _delay)))
  {
    on();
  }

}

void TimedDevice::deactivate(int h, int d)
{
  bool isScheduled = timer.isScheduled(h,d);

  if (!isScheduled)
  {
    off();
    return;
  }

  if (_active && (millis() > _lastActivation + _timeout))
  {
    off();
  }

}


// activate/deactivate device according to timer schedule
void TimedDevice::checkTimer(int h, int d)
{
  bool isScheduled = timer.isScheduled(h,d);

  if (!isScheduled)
  {
    off();
    return;
  }

  if(!_active)
  {
    on();
  }
}

long TimedDevice::getActivations()
{
	return _activations;
}

void TimedDevice::checkTimeout()
{
  if (_active && (millis() > _lastActivation + _timeout))
  {
    off();
  }
}
