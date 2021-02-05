

#include "Timer.h"
#include "TimedDevice.h"
#include "Relay.h"


Relay::Relay(int pinId)
{
  _pinId = pinId;
};


void Relay::on()
{
    _active = 1;
    digitalWrite(_pinId, HIGH);
    _activations++;
    _lastActivation = millis();
}

void Relay::off()
{
    _active = 0;
    digitalWrite(_pinId, LOW);
}
