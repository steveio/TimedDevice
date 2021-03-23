/**

TimedDevice.h

Provides a based class TimedDevice including a Timer defining when a device should be on/off
attributes track device status, number of activations, time of last activation etc

Device classes (lamps, pumps etc) extend TimedDevice


*/


#ifndef TIMED_DEVICE_H_
#define TIMED_DEVICE_H_


#include <Arduino.h>
#include <Timer.h>


class TimedDevice {
    public:
      TimedDevice();

      void initTimer(Timer t);
      bool isActive();
      void on();
      void off();
      void toggle();
      void activate(int h);
      void deactivate(int h, int d);
      void checkTimer(int h, int d);
      void checkTimeout();
      long getActivations();


      Timer timer;

    protected:

      bool _active = 0; // device status on/off
      unsigned long _lastActivation = 0;
      unsigned long _activations = 0;
      unsigned long _timeout; // auto-deactivate device after _timoeout milliseconds
      unsigned long _delay; // min time in ms between activations

};


#endif
