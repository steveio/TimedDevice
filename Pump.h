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
    void on();
    void off();
    void activate(int h, int d);
    void deactivate(int h, int d);

    int pinId; // digital pin relay is wired to
    unsigned long duration; // pump active duration
    unsigned long delay; // min time in ms between pump activations

  protected:

};


#endif;
