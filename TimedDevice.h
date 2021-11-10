/**

TimedDevice.h

Provides a based class TimedDevice including a Timer defining when a device should be on/off
attributes track device status, number of activations, time of last activation etc

Device classes (lamps, pumps etc) extend TimedDevice

Link - https://github.com/steveio/TimedDevice
Copyright (C) 2020  Steven G Edwards


*/


#ifndef TIMED_DEVICE_H_
#define TIMED_DEVICE_H_


#include <Timer.h>


class TimedDevice {
    public:
      TimedDevice();

      void initTimer(Timer t);
      bool isActive();
      void update(int h, int d, unsigned long ts);
      void update(unsigned long ts);
      long getActivations();

      Timer timer;

    protected:

      virtual void on();
      virtual void off();
      bool activate();
      bool deactivate();

      bool _active = 0; // device status on/off
      unsigned long _lastActivation = 0;
      unsigned long _activations = 0;
      unsigned long _duration; // auto-deactivate device after _timoeout milliseconds
      unsigned long _delay; // min time in ms between activations

      unsigned long _millis = 0;

};


#endif
