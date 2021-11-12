#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

#include <Timer.h>
#include <RecurringTimer.h>


using namespace std;

timeb t_start;
RecurringTimer timer;

class DeviceClass
{
public:
   bool Activate() { printf("DeviceClass::Activate\n"); return true; };
   bool DeActivate() { printf("DeviceClass::DeActivate\n"); return true; };
};

DeviceClass device;

void activateDevice()
{
  device.Activate();
}

void (*pt2Function)() = NULL;
//bool (DeviceClass::*ptCallback)() = NULL;


unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){}
}


void setup()
{
  printf("RecurringTimer test\n");

  unsigned long ts = millis() / 1000;
  unsigned long interval = 1000 * 5;

  /**
  // start timer from specific point in time

  struct tmElements_t t1_on;

  t1_on.Hour = 9;
  t1_on.Min = 30;
  t1_on.Sec = 0;

  timer.init(TIMER_MILLIS_RECURRING, ts, &t1_on, interval);
  **/

  // start timer from now
  timer.init(TIMER_MILLIS_RECURRING, ts, interval);

  // set callback func
  pt2Function = activateDevice;
  if (pt2Function > 0)
  {
    timer.setCallback(pt2Function);
  }

  /*
  ptCallback = &DeviceClass::Activate;
  if(ptCallback == &DeviceClass::Activate)
  */

  /* init timer as pointer
  RecurringTimer* timer = new RecurringTimer();
  timer->init(TIMER_MILLIS_RECURRING, ts, &t1_on, interval);
  */

}

void loop()
{
  printf("timer.update()...\n");

  unsigned long ts = millis() / 1000;

  if (timer.update(ts))
  {
    printf("Active\n");
  }

  delay(1000);
}

int main()
{
  setup();

  while(1)
  {
    loop();
  }

}
