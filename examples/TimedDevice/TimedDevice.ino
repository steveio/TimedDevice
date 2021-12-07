/** 
 *  Smart Indoor Garden
 *  
 *  Demonstrates a microcontroller managed indoor seed propagator environment
 * 
 *  -- Scheduled (relay) activation for LED LAMP(s)
 *  -- Scheduled 5v pump activation for watering
 *  -- Soil moisture / temperature monitoring
 * 
 * Arduino Pro Mini 3.3v 
 * RTC DS1307
 * 2x 5v water pump attached via relay
 * Lamp via mains 240v AC relay
 * Soil Moisture Capacitive v1.2 sensor
 * DHT22 Temperature / Humidity Sensor
 * 
 * Minimal (low memory) standalone mcu optimised
 *
 * @requires Library TimedDevice ( https://github.com/steveio/TimedDevice )
 *
 */

#include <Wire.h>
#include "RTClib.h"
//#include "SSD1306Ascii.h"
//#include "SSD1306AsciiWire.h"
#include <DHT.h>;
#include "Timer.h"
#include "RecurringTimer.h"
#include "Pump.h"
#include "Relay.h"


// SSD1306 Ascii 
// 0X3C+SA0 - 0x3C or 0x3D
//#define I2C_ADDRESS 0x3C
//#define RST_PIN -1
//SSD1306AsciiWire oled;


RTC_DS1307 rtc;
DateTime dt;
char dtm[16], buf[2];
int nextEvent;


unsigned long startTime = 0;
unsigned long sampleInterval = 1000;  // sample frequency in ms
unsigned long sampleTimer = 0;


// GPIO Pins & mapping to devices
const int r1Pin = 10; // pump relay #1
const int r2Pin = 11; // fan relay #2
const int r3Pin = 12; // lamp relay
const int s1Pin = A1; // soil moisture sensor #1
const int s2Pin = 9;  // DHT22


// master on/off switches
bool pumpEnabled = true;
bool lampEnabled = true;


RecurringTimer pump1Timer;
Pump pump1(r1Pin);


// Timer 32 bit bitmask defines hours (24h) device is on | off
// 0b 00000000 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
Timer lamp1Timer;
long lamp1TimerBitmask =0b00000000000111111111111111000000; // 6am - 9pm
Relay lamp1(r3Pin);


long fan1TimerBitmask =0b00000000000100100100100100000000; // every 3 hours from 8am
int fan1DayofWeek = 0b00101010; // (<sat -> sun>) every mon / weds / fri

Timer fan1Timer;
Relay fan1(r2Pin);


// Soil Moisture Capacitive v1.2 sensor calibration
int airVal = 680;
int waterVal = 326;
const int intervals = (airVal - waterVal) / 3;

int soilMoistureVal[2];
int soilMoistureStatusId[2];

// DHT22 Temperature / Humidity
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(s2Pin, DHTTYPE);
float humidity, tempC;


void activatePump()
{
  Serial.println("Pump1:on");
  dt = rtc.now();
  pump1.on(dt.unixtime());
}

void deactivatePump()
{
  Serial.println("Pump1:off");
  dt = rtc.now();
  pump1.off(dt.unixtime());
}

// take an average from a sensor returning an int value
int readSensorAvg(int pinId, int numSample, int delayTime)
{
  int v = 0;
  for(int i=0; i<numSample; i++)
  {
    v += analogRead(pinId);
    delay(delayTime);
  }

  v = v / numSample;
  return v;
}

/**
 * Read & categorise soil moisture sensor data 
 * @param int pin id
 * @param int soil moisture value (from sensor reading)
 * @param int soil moisture level: { V_WET 0, WET 1, DRY 2, V_DRY 3 }
 */
void readSoilMoisture(int pinId, int * v, int * id)
{

  // take 3 samples with a 200 ms delay
  *v = readSensorAvg(pinId, 3, 200);

  if(*v < airVal && (*v > (airVal - intervals))) // Dry  > 562
  {
    *id = 2;
  }
  else if(*v < airVal && (*v > (airVal - intervals * 2))) // Wet > 444 - 562
  {
    *id = 1;
  }
  else
  {
    *id = 0; // V Wet 326 - 444
  }

}

void readDHT22()
{
    humidity = dht.readHumidity();
    tempC = dht.readTemperature();
}

/*
void displayOLED()
{

  oled.clear();
  oled.set1X();
  
  sprintf(dtm, "%02d/%02d/%02d %02d:%02d" , dt.day(),dt.month(),dt.year(),dt.hour(),dt.minute());
  oled.println(dtm);

  // LAMP 1
  oled.print(F("L1: "));
  if (lamp1.isActive())
  {
    oled.print("1");
  } else {
    oled.print("0");
  }

  oled.print(F("/"));

  if (lamp1.timer.isScheduled(dt.hour()))
  {
    oled.print("1");
  } else {
    oled.print("0");
  }

  oled.print(F("/"));

  nextEvent = lamp1.timer.getNextEvent(dt.hour());
  sprintf(buf,"%02d",nextEvent);
  oled.print(buf);
  oled.println(":00");

  // PUMP 1
  oled.print(F("P1: "));
  if (pump1.isActive())
  {
    oled.print("1");
  } else {
    oled.print("0");
  }

  oled.print(F("/"));

  unsigned long duration = pump1Timer.getDuration();
  oled.print(duration);

  oled.print(F("/"));
  unsigned long nextTs = pump1Timer.getNextEvent();

  DateTime dt1((uint32_t) nextTs);
  sprintf(dtm, "%02d/%02d/%02d %02d:%02d" , dt1.day(),dt1.month(),dt1.year(),dt1.hour(),dt1.minute());
  oled.println(dtm);

  oled.println("");

  oled.print(F("Soil: "));
  sprintf(buf,"%02d",soilMoistureVal[0]);
  oled.print(buf);
  oled.print("/");
  sprintf(buf,"%02d",soilMoistureStatusId[0]);
  oled.println(buf);

  oled.print(F("Env: "));
  oled.print(tempC);
  oled.print(F("/"));
  oled.print(humidity);
  oled.println(F("%"));

}

*/

void displaySerial()
{

    Serial.println("");
    sprintf(dtm, "%02d/%02d/%02d %02d:%02d:%02d" , dt.day(),dt.month(),dt.year(),dt.hour(),dt.minute(),dt.second());
    Serial.println(dtm);

    // LAMP 1
    Serial.print(F("Lamp1: "));
    if (lamp1.isActive())
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    if (lamp1.timer.isScheduled(dt.hour()))
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }

    Serial.print(F(" / "));

    nextEvent = lamp1.timer.getNextEvent(dt.hour());
    sprintf(buf,"%02d",nextEvent);
    Serial.print(buf);
    Serial.println(":00");


    // PUMP 1
    Serial.print(F("P1: "));
    if (pump1.isActive())
    {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
  
    Serial.print(F("/"));
  
    unsigned long duration = pump1Timer.getDuration();
    Serial.print(duration);
  
    Serial.print(F("/"));

    unsigned long interval = pump1Timer.getInterval();
    Serial.print(interval);
  
    Serial.print(F("/"));

    unsigned long nextTs = pump1Timer.getNextEvent();
    DateTime dt1((uint32_t) nextTs);
    sprintf(dtm, "%02d-%02d-%02d %02d:%02d:%02d" , dt1.day(),dt1.month(),dt1.year(),dt1.hour(),dt1.minute(), dt1.second());
    Serial.print(dtm);

    Serial.print(F(" / "));

    nextTs = pump1Timer.getTimeout();
    DateTime dt2((uint32_t) nextTs);
    sprintf(dtm, "%02d-%02d-%02d %02d:%02d:%02d" , dt2.day(),dt2.month(),dt2.year(),dt2.hour(),dt2.minute(), dt2.second());
    Serial.println(dtm);

    Serial.print(F("Soil1: "));
    sprintf(buf,"%02d",soilMoistureVal[0]);
    Serial.print(buf);
    Serial.print("/");
    sprintf(buf,"%02d",soilMoistureStatusId[0]);
    Serial.println(buf);

    Serial.print(F("Temp/Hum: "));
    Serial.print(tempC);
    Serial.print((char)223);
    Serial.print(F("C / "));
    Serial.print(humidity);
    Serial.print(F("%"));

    Serial.println("");

}


void setup() {

  Serial.begin(115200);

  startTime = millis();

  Wire.begin();
  Wire.setClock(400000L);

  rtc.begin();
  dt = rtc.now();
  DateTime arduino_t = DateTime(__DATE__, __TIME__);

  // sync RTC w/ arduino time @ compile time
  if (dt.unixtime() != arduino_t.unixtime())
  {
    rtc.adjust(arduino_t.unixtime());
  }

  // Sensor / Relay (pump/lamp) Pins
  pinMode(s1Pin, INPUT);
  pinMode(s2Pin, INPUT);

  pinMode(r1Pin, OUTPUT);
  digitalWrite(r1Pin, HIGH);
  pinMode(r2Pin, OUTPUT);
  digitalWrite(r2Pin, HIGH);

  pinMode(r3Pin, OUTPUT);
  pinMode(r3Pin, HIGH);

  unsigned long ts = dt.unixtime();
  unsigned long interval = 15000;
  unsigned long duration = 5000;

  // start timer from now
  pump1Timer.init(TIMER_MILLIS_RECURRING, ts, interval, duration);

  // set callback func
  pt2Function timerActiveCallback = activatePump;
  pt2Function timerTimeoutCallback = deactivatePump;

  pump1Timer.setCallback(timerActiveCallback, CALLBACK_TIMER_ACTIVE);
  pump1Timer.setCallback(timerTimeoutCallback, CALLBACK_TIMER_TIMEOUT);

  
  lamp1Timer.init(TIMER_HOUR_OF_DAY, &lamp1TimerBitmask);
  lamp1.initTimer(lamp1Timer);


  fan1Timer.init(TIMER_DAY_OF_WEEK, &fan1TimerBitmask, &fan1DayofWeek);
  fan1.initTimer(fan1Timer);


  dht.begin();

  /* OLED LCD Display
  #if RST_PIN >= 0
    oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
  #endif // RST_PIN >= 0
  oled.setFont(Adafruit5x7);
  oled.clear();

  sprintf(dtm, "%02d/%02d/%02d %02d:%02d" , dt.day(),dt.month(),dt.year(),dt.hour(),dt.minute());
  oled.println(dtm);
  */

  sampleTimer = millis();
}

void loop() {

  // check & update timed device status 
  dt = rtc.now();

  if (lampEnabled)
  {
    lamp1.update(dt.unixtime());
  }

  if (pumpEnabled)
  {
    if (pump1Timer.update(dt.unixtime()))
    {
      Serial.println("Active");
    }
  }

  fan1.update();

  if (millis() >= sampleTimer + sampleInterval)
  {    
    readSoilMoisture(s1Pin, &soilMoistureVal[0], &soilMoistureStatusId[0]);
    readDHT22();

    //displayOLED();
    displaySerial();

    sampleTimer = millis();
  }
}
