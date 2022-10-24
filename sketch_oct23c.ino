#include <Wire.h>
#include <VL53L0X.h>
#include "SPI.h"
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>
#include "RTClib.h"
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
  display.setCursor(0,11);  display.print (">PARAMETERS");
  display.setCursor(0,20);  display.print (" DATA RECORD");
  display.setCursor(0,29);  display.print (" DISPLAY");
  display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print (" PROJECT INFO");
  refresh();
}

if (pic == 2)
{
  header();
  display.setCursor(0,11);  display.print (" PARAMETERS");
  display.setCursor(0,20);  display.print (">DATA RECORD");
  display.setCursor(0,29);  display.print (" DISPLAY");
  display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print (" PROJECT INFO");
  refresh();
}

if (pic == 3)
{
  header();
  display.setCursor(0,11);  display.print (" PARAMETERS");
  display.setCursor(0,20);  display.print (" DATA RECORD");
  display.setCursor(0,29);  display.print (">DISPLAY");
  display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print (" PROJECT INFO");
  refresh();
}

if (pic == 4)
{
  header();
  display.setCursor(0,11);  display.print (" PARAMETERS");
  display.setCursor(0,20);  display.print (" DATA RECORD");
  display.setCursor(0,29);  display.print (" DISPLAY");
  display.setCursor(0,47);  display.print (">HELP");
  display.setCursor(0,56);  display.print (" PROJECT INFO");
  refresh();
}

if (pic == 5)
{
  header();
  display.setCursor(0,11);  display.print (" PARAMETERS");
  display.setCursor(0,20);  display.print (" DATA RECORD");
  display.setCursor(0,29);  display.print (" DISPLAY");
  display.setCursor(0,47);  display.print (" HELP");
  display.setCursor(0,56);  display.print (">PROJECT INFO");
  refresh();
}




  
if(digitalRead(BUTTON_CENTER)==LOW){
    badMenu();
  }
  
  //Check 
  button_down_now_state = digitalRead (BUTTON_DOWN);
 if (button_down_old_state == LOW && button_down_now_state == HIGH) {        //if low -> high
      laser_state = !laser_state;                        //switch state: true <-> false
      digitalWrite(LASER, laser_state);
        }
      button_down_old_state = button_down_now_state;       //save button state
      //delay(500);

  
}//end of loop

void badApple(){
  display.
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

void header()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);  display.print("rg-electronics");
  display.drawLine (0,9,128,9, WHITE);
}


void refresh()
{
  display.display();
  delay(00);
  display.clearDisplay();
}
