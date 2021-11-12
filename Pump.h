/**

Pump.h

Pump represents a 5v water pump activated via a relay switch

For a scheduled timer based activation:
  - Timeout defines active time (on duration) in ms
  - Delay is interval in ms between activations

If a pump is timer scheduled to be on between 9am and 10am
For 3x 10 minute activations Timeout = 10mins, Delay 10mins)
For 3x 1min activations per Hour Timeout = 60000 ms, Delay = 1140000 ms

*/

#ifndef PUMP_H_
#define PUMP_H_

#include <Arduino.h>
#include <TimedDevice.h>

class Pump: public TimedDevice
{

  public:
    Pump(int pinId, unsigned long duration);
    Pump(int pinId, unsigned long duration, unsigned long delay);
    void on(unsigned long ts);
    void off(unsigned long ts);

    int _pinId; // digital pin relay is wired to

  protected:

};


#endif;
