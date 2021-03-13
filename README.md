Arduino Timed Device Library

Simple & lightweight timer based scheduling for on/off devices

Supports recurring timers:
*  Bitmap timers w/ hour precision
*  On time + Duration w/ timeout timer
*  On/Off timers w/ hour and minute precision
*  Day of Week/Month scheduling 

Device classes extend a base class <TimedDevice>.  A class <Timer> defines a schedule for when a device is on/off

<TimedDevice> class maintains attributes to track number of activations, time of last activation.

Device classes (lamps, pumps etc) extend TimedDevice and can implement required domain specific functionality

Supported on Arduino & ESP8266/32 microcontroller platforms

Optimisation is for low memory ATMega328p devices, typically memory useage for a single device is 1.7k to 4k for a complex sketch with multiple devices.
