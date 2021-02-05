/**

Pump.h

Pump represents a 5v water pump activated via a relay switch

Duration and delay define running time (on activation) and interval (delay) between activations

*/

#ifndef PUMP_H_
#define PUMP_H_

#include <TimedDevice.h>


class Pump: public TimedDevice
{

  public:
    Pump(int pinId, unsigned long duration, unsigned long delay);
    Pump(int pinId, long timeout);
    void on();
    void off();
    void activate(int h);
    void deactivate(int h, int d);
    void checkTimeout();

    int _pinId; // digital pin relay is wired to
    unsigned long _duration; // pump active duration
    unsigned long _delay; // min time in ms between pump activations
    unsigned long _timeout; // auto-deactivate after timoeout milliseconds

  protected:

};


#endif;
