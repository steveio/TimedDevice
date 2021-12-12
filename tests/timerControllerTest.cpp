/**


@compile
g++ -I/home/stevee/Arduino/libraries/TimedDevice timerControllerTest.cpp /home/stevee/Arduino/libraries/TimedDevice/Timer.cpp /home/stevee/Arduino/libraries/TimedDevice/RecurringTimer.cpp  /home/stevee/Arduino/libraries/TimedDevice/TimerController.cpp -o timerControllerTest -fpermissive


**/

#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

#include <Timer.h>
#include <RecurringTimer.h>
#include <TimerController.h>

using namespace std;

timeb t_start;
RecurringTimer timer1(1), timer2(2), timer3(3);
TimerController timerController = TimerController::getInstance();


class DeviceClass
{
public:
   DeviceClass(int id)
   {
     id = id;
   }
   bool Activate() {
     printf("DeviceClass( %d )::Activate\n", id); return true;
   };
   bool DeActivate() { printf("DeviceClass::DeActivate\n"); return true; };
   int id;
};

DeviceClass device1(1);
DeviceClass device2(2);
DeviceClass device3(3);

void activateDevice1()
{
  device1.Activate();
}

void activateDevice2()
{
  device2.Activate();
}

void activateDevice3()
{
  device3.Activate();
}


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

  printf("Setup timers\n");

  unsigned long ts = millis() / 1000;
  unsigned long interval1 = 1000 * 5;
  unsigned long interval2 = 1000 * 10;
  unsigned long interval3 = 1000 * 15;
  unsigned long duration = 2000;

  timer1.init(TIMER_MILLIS_RECURRING, ts, interval1, duration);
  timer2.init(TIMER_MILLIS_RECURRING, ts, interval2, duration);
  timer3.init(TIMER_MILLIS_RECURRING, ts, interval3, duration);

  pt2Function timer1ActiveCallback = activateDevice1;
  pt2Function timer2ActiveCallback = activateDevice2;
  pt2Function timer3ActiveCallback = activateDevice3;

  timer1.setCallback(timer1ActiveCallback, CALLBACK_TIMER_ACTIVE);
  timer2.setCallback(timer2ActiveCallback, CALLBACK_TIMER_ACTIVE);
  timer3.setCallback(timer3ActiveCallback, CALLBACK_TIMER_ACTIVE);

  printf("TimerContoller add timers\n");

  timerController.add(timer1);
  timerController.add(timer2);
  timerController.add(timer3);

}

void loop()
{
  printf("timerController.update()\n");

  unsigned long ts = millis() / 1000;

  timerController.update(ts);

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
