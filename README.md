Arduino Timed Devices

Simple timer based scheduling for on/off devices

Provides a based class TimedDevice including a Timer defining when a device should be on/off
and attributes to track number of activations, time of last activation etc

Device classes (lamps, pumps etc) extend TimedDevice

Timer type is recurring and bitmap based defining device status

Granularity (time units) are hours of day and day of week or month
