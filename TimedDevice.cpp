
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

// activate/deactivate device according to timer schedule
void TimedDevice::scheduledActivation(int h, int d)
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
