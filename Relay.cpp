

#include "Timer.h"
#include "TimedDevice.h"
#include "Relay.h"


Relay::Relay(int pinId)
{
  _pinId = pinId;
};


void Relay::on(unsigned long ts)
{
  digitalWrite(_pinId, HIGH);
  _active = true;
  _activations++;
  _lastActivation = ts;
}

void Relay::off(unsigned long ts)
{
  digitalWrite(_pinId, LOW);
  _active = false;
  _lastDeActivation = ts;
}
