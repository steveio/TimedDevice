

#include "Timer.h"
#include "TimedDevice.h"
#include "Relay.h"


Relay::Relay(int pinId)
{
  _pinId = pinId;
};


void Relay::on()
{
  digitalWrite(_pinId, HIGH);
  _active = true;
  _activations++;
  _lastActivation = millis();
}

void Relay::off()
{
  digitalWrite(_pinId, LOW);
  _active = false;
}
