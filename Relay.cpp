

#include "Timer.h"
#include "TimedDevice.h"
#include "Relay.h"


Relay::Relay(int pinId)
{
  _pinId = pinId;
};


void Relay::on()
{
    _active = true;
    digitalWrite(_pinId, HIGH);
    _activations++;
    _lastActivation = millis();
}

void Relay::off()
{
    _active = false;
    digitalWrite(_pinId, LOW);
}
