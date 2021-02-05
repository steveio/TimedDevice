

#include "Timer.h"
#include "TimedDevice.h"
#include "Pump.h"



Pump::Pump(int pinId, unsigned long duration, unsigned long delay)
{
  _pinId = pinId;
  _duration = duration; // pump active duration
  _delay = delay; // min time in ms between pump activations
};

Pump::Pump(int pinId, long timeout)
{
  _pinId = pinId;
  _timeout = timeout;
};


void Pump::on()
{
    digitalWrite(_pinId, LOW);
    _active = 1;
    _activations++;
    _lastActivation = millis();
}

void Pump::off()
{
    _active = 0;
    digitalWrite(_pinId, HIGH);
}

// activate/deactivate device according to timer schedule, w/ duration & interval (delay)
void Pump::activate(int h)
{
  bool isScheduled = timer.isScheduled(h);

  Serial.println("Pump Sched: ");
  Serial.println(isScheduled);

  if (!isScheduled)
  {
    return;
  }

  if(!_active && (_lastActivation == 0 || (millis() > _lastActivation + _delay)))
  {
    on();
  }

  if (_active && (millis() > _lastActivation + _duration))
  {
    off();
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

  if (_active && (millis() > _lastActivation + _duration))
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
