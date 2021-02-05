/**

Relay.h

Relay represents a switchable relay activated device typically 5v or AC 240 v mains

*/


#ifndef RELAY_H_
#define RELAY_H_

#include <TimedDevice.h>


class Relay: public TimedDevice
{

  public:
    Relay(int pinId);
    void on();
    void off();

    int _pinId; // digital pin relay is wired to

  protected:

};


#endif;
