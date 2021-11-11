

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
  digitalWrite(_pinId, LOW);
  _active = true;
  _activations++;
  _lastActivation = millis();
}

void Pump::off()
{
  digitalWrite(_pinId, HIGH);
  _active = false;
}
