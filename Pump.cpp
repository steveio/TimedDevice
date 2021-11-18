

#include "Timer.h"
#include "TimedDevice.h"
#include "Pump.h"

Pump::Pump(int pinId)
{
  _pinId = pinId;
};


Pump::Pump(int pinId, unsigned long duration)
{
  _pinId = pinId;
  _duration = duration;
};


Pump::Pump(int pinId, unsigned long duration, unsigned long delay)
{
  _pinId = pinId;
  _duration = duration; // pump active duration
  _delay = delay; // min time in ms between pump activations
};


void Pump::on(unsigned long ts)
{
  digitalWrite(_pinId, LOW);
  _active = true;
  _activations++;
  _lastActivation = ts;
}

void Pump::off(unsigned long ts)
{
  digitalWrite(_pinId, HIGH);
  _active = false;
  _lastDeActivation = ts;

}
