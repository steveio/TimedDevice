

#include "Timer.h"
#include "TimedDevice.h"
#include "Pump.h"


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


void Pump::on()
{
  _active = true;
  digitalWrite(_pinId, LOW);
  _activations++;
  _lastActivation = millis();
}

void Pump::off()
{
  _active = false;
  digitalWrite(_pinId, HIGH);
}
