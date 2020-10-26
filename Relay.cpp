

#include "Timer.h"
#include "TimedDevice.h"
#include "Relay.h"


Relay::Relay(int pinId)
{
  pinId = pinId;
};


void Relay::on()
{
    active = 1;
    digitalWrite(pinId, HIGH);
    activations++;
    lastActivation = millis();
}

void Relay::off()
{
    active = 0;
    digitalWrite(pinId, LOW);
}
