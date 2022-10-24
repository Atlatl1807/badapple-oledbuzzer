#include <Wire.h>
#include <VL53L0X.h>
#include "SPI.h"
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>
#include "RTClib.h"
#include <U8g2lib.h>
//#include "timer.h"

#define BUTTON_UP 10
#define BUTTON_CENTER 9
#define BUTTON_DOWN 8

#define BUZZER 12
#define LASER 13
#define PIXEL_COUNT 1
#define PIXEL_PIN   6


Adafruit_SH1106 display(7);
VL53L0X sensor;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
//auto timer = timer_create_default();
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
boolean button_down_now_state = HIGH;
boolean button_down_old_state = LOW;
boolean laser_state = HIGH;
boolean isRtc = true;

long lastmillis = 0;
long maxtime = 30000;

int pic = 0;
int maxPics = 4;



void setup() {
  
  Wire.begin();
  //Serial.begin(115200);
  //timer.every(9000, keypower);
  rtc.begin(); //starts rtc chip
  sensor.init(); //initalize sensor 
  sensor.setTimeout(500); //sets distance sensor reading timing
  sensor.startContinuous(); //sets distance sensor reading

  pinMode(BUTTON_UP,INPUT_PULLUP);
  pinMode(BUTTON_CENTER,INPUT_PULLUP);
  pinMode(BUTTON_DOWN,INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
  pinMode(LASER,OUTPUT);
  pinMode(PIXEL_PIN,OUTPUT);
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  //Serial.println("setup almost done");
  delay(2000);
}

void loop() {
  //timer.tick();
if (millis() >= (lastmillis + maxtime))
{
    pic = 0;
}

  if (pic == 0)
{
  DateTime now = rtc.now();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.setTextSize(1);
  display.print(' ');
  display.print(' ');
  display.print(' ');
  display.print(now.second(), DEC);
  display.println();
  display.setCursor(0,30);
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print(' ');
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.setCursor(0,40);
  display.print("Temperature: ");
  display.print(rtc.getTemperature());
  display.print(" C");
  display.setCursor(0,50);
  display.print("Distance");
  display.print(':');
  display.print(sensor.readRangeContinuousMillimeters());
  display.print("MM");
  display.display();
  refresh();
}

if (pic == 1)
{
  header();
  display.setCursor(0,11);  display.print (">CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,47);  display.print (" LASER TOGGLE");
  display.setCursor(0,56);  display.print (" test2");
  refresh();
}

if (pic == 2)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (">BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,47);  display.print (" LASER TOGGLE");
  display.setCursor(0,56);  display.print (" test2");
  refresh();
}

if (pic == 3)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (">EXECUTE ATTACK");
  display.setCursor(0,47);  display.print (" LASER TOGGLE");
  display.setCursor(0,56);  display.print (" test");
  refresh();
}

if (pic == 4)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,47);  display.print (">LASER TOGGLE");
  display.setCursor(0,56);  display.print (" test");
  refresh();
}

if (pic == 5)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,47);  display.print (">LASER TOGGLE");
  display.setCursor(0,56);  display.print (" test");
  refresh();
}

if(digitalRead(BUTTON_DOWN)==LOW)
{
    if(pic>=0 && pic<10)
  {
    if (pic >= maxPics)
    {
      pic=1;
    }
    else if(pic < maxPics)
    {
      pic++;
    }
  }
}

if(digitalRead(BUTTON_UP)==LOW)
{
    if(pic > 0 )
  {
    if (pic <= 1)
    {
      pic = maxPics;
    }
    else if(pic < maxPics)
    {
      pic--;
    }
  }
}

if(digitalRead(BUTTON_CENTER)==LOW)
{
    if(pic>=0 && pic<10)
  {
    if (pic = 1)
    {
      pic=0;
    }
    else if(pic = 2)
    {
      badApple();
    }
    else if(pic = 3)
    {
      badUSB();
    }
    else if(pic = 3)
    {
      laser();
    }
  }
}

  
} //end loop

void badApple()
{
  
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 830, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1108, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 281.25);
    delay(312.5);
    tone(BUZZER, 932, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 830, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 830, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 281.25);
    delay(312.5);
    tone(BUZZER, 830, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 739, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 698, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 466, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 698, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 739, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 698, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 622, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 587, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 830, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 281.25);
    delay(312.5);
    tone(BUZZER, 830, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1108, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1244, 281.25);
    delay(312.5);
    tone(BUZZER, 1244, 281.25);
    delay(312.5);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1479, 281.25);
    delay(312.5);
    tone(BUZZER, 1244, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1396, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1479, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1661, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1864, 281.25);
    delay(312.5);
    tone(BUZZER, 1661, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1479, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1661, 281.25);
    delay(312.5);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1479, 281.25);
    delay(312.5);
    tone(BUZZER, 1661, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 562.5);
    delay(625.0);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 281.25);
    delay(312.5);
    tone(BUZZER, 698, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 466, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 698, 281.25);
    delay(312.5);
    tone(BUZZER, 698, 281.25);
    delay(312.5);
    tone(BUZZER, 739, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 622, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 554, 281.25);
    delay(312.5);
    tone(BUZZER, 554, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 466, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 622, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 562.5);
    delay(625.0);
    tone(BUZZER, 622, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 739, 281.25);
    delay(312.5);
    tone(BUZZER, 698, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 739, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 830, 281.25);
    delay(312.5);
    tone(BUZZER, 622, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 1125.0);
    delay(1250.0);
    tone(BUZZER, 830, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1108, 281.25);
    delay(312.5);
    tone(BUZZER, 1244, 562.5);
    delay(625.0);
    tone(BUZZER, 1244, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1396, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1479, 281.25);
    delay(312.5);
    tone(BUZZER, 1396, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 932, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1479, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1244, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 1108, 281.25);
    delay(312.5);
    tone(BUZZER, 1108, 281.25);
    delay(312.5);
    tone(BUZZER, 1244, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 932, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1244, 562.5);
    delay(625.0);
    tone(BUZZER, 1244, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1396, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1479, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1661, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1396, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 1479, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 1661, 281.25);
    delay(312.5);
    tone(BUZZER, 1174, 421.2890625);
    delay(468.098958333);
    tone(BUZZER, 932, 422.4609375);
    delay(469.401041667);
    tone(BUZZER, 1864, 281.25);
    delay(312.5);
    tone(BUZZER, 1661, 281.25);
    delay(312.5);
    tone(BUZZER, 1479, 281.25);
    delay(312.5);
    tone(BUZZER, 1396, 281.25);
    delay(312.5);
    tone(BUZZER, 1479, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 466, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 587, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 466, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 880, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 587, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1046, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 562.5);
    delay(625.0);
    tone(BUZZER, 880, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 783, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 587, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 466, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 466, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 587, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 698, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 466, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 880, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 587, 281.25);
    delay(312.5);
    tone(BUZZER, 783, 281.25);
    delay(312.5);
    tone(BUZZER, 587, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 783, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1046, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 562.5);
    delay(625.0);
    tone(BUZZER, 880, 281.25);
    delay(312.5);
    tone(BUZZER, 932, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1174, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1396, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1760, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1864, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 1174, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 2093, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1864, 562.5);
    delay(625.0);
    tone(BUZZER, 1760, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1567, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1174, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 932, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1174, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1396, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 932, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1760, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1864, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1174, 281.25);
    delay(312.5);
    tone(BUZZER, 1567, 281.25);
    delay(312.5);
    tone(BUZZER, 1174, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1567, 140.0390625);
    delay(155.598958333);
    tone(BUZZER, 1760, 141.2109375);
    delay(156.901041667);
    tone(BUZZER, 1864, 1125.0);
    delay(1250.0);

}

void header()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);  
  display.print("badMenu!!");
  display.drawLine (0,9,128,9, WHITE);
}


void refresh()
{
  display.display();
  delay(00);
  display.clearDisplay();
}

void badUSB(){
  delay(2000);
  Keyboard.begin();
  delay(500);
  Keyboard.press(KEY_LEFT_GUI);
  delay(500);
  Keyboard.press('r');
  delay(500);
  Keyboard.release(KEY_LEFT_GUI);
  Keyboard.release('r');
  Keyboard.print("https://www.youtube.com/watch?v=3_-a9nVZYjk?t=11s");
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(500);
  Keyboard.press(KEY_LEFT_GUI);
  delay(500);
  Keyboard.press('r');
  delay(500);
  Keyboard.release(KEY_LEFT_GUI);
  Keyboard.release('r');
  Keyboard.print("http://fakeupdate.net/win10ue");
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
  delay(1000);
  Keyboard.press(KEY_F11);
  Keyboard.release(KEY_F11);
  Keyboard.end();
  delay(500); 
}

void laser()
{
  //button_down_now_state = digitalRead (BUTTON_DOWN);
  //if (button_down_old_state == LOW && button_down_now_state == HIGH) {        //if low -> high
      laser_state = !laser_state;                        //switch state: true <-> false
      digitalWrite(LASER, laser_state);
  //button_down_old_state = button_down_now_state;       //save button state
      delay(500);
}
