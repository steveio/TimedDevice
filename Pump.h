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

#include <TimedDevice.h>

class Pump: public TimedDevice
{

  public:
    Pump(int pinId, unsigned long timeout);
    Pump(int pinId, unsigned long timeout, unsigned long delay);
    void on();
    void off();
    void activate(int h);
    void deactivate(int h, int d);
    void checkTimeout();

    int _pinId; // digital pin relay is wired to
    unsigned long _timeout; // pump active duration ms
    unsigned long _delay; // min time in ms between pump activations

  protected:

};


#endif;
