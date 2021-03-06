

#include "Timer.h"
#include "TimedDevice.h"
#include "Pump.h"


Pump::Pump(int pinId, unsigned long timeout)
{
  _pinId = pinId;
  _timeout = timeout;
};


Pump::Pump(int pinId, unsigned long timeout, unsigned long delay)
{
  _pinId = pinId;
  _timeout = timeout; // pump active duration
  _delay = delay; // min time in ms between pump activations
};


void Pump::on()
{
    digitalWrite(_pinId, LOW);
    _active = true;
    _activations++;
    _lastActivation = millis();
}

void Pump::off()
{
    _active = false;
    digitalWrite(_pinId, HIGH);
}

// activate/deactivate device according to timer schedule, w/ duration & interval (delay)
void Pump::activate(int h)
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

void Pump::deactivate(int h, int d)
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

void Pump::checkTimeout()
{
  if (_active && (millis() > _lastActivation + _timeout))
  {
    off();
  }
}
