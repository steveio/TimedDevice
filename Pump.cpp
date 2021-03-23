

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
