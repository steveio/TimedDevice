

#include "Timer.h"
#include "TimedDevice.h"
#include "Pump.h"


Pump::Pump(int pinId, unsigned long duration, unsigned long delay)
{
  pinId = pinId;
  duration = duration; // pump active duration
  delay = delay; // min time in ms between pump activations
};

Pump::Pump(int pinId, long timeout)
{
  pinId = pinId;
  timeout = timeout;
};


void Pump::on()
{
    active = 1;
    digitalWrite(pinId, LOW);
    activations++;
    lastActivation = millis();
}

void Pump::off()
{
    active = 0;
    digitalWrite(pinId, HIGH);
}

// activate/deactivate device according to timer schedule, respect activation interval (delay)
void Pump::activate(int h, int d)
{
  bool isScheduled = timer.isScheduled(h,d);

  if (!isScheduled)
  {
    return;
  }

  if(!active && (lastActivation == 0 || (millis() > lastActivation + delay)))
  {
    on();
  }

  if (active && (millis() > lastActivation + duration))
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

  if (active && (millis() > lastActivation + duration))
  {
    off();
  }

}

void Pump::checkTimeout()
{
  if (active && (millis() > lastActivation + timeout))
  {
    off();
  }
}
