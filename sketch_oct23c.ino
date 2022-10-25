#include <Wire.h>
#include <VL53L0X.h>
#include "SPI.h"
//#include <Adafruit_GrayOLED.h>
#include <Adafruit_SH1106.h>
//#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>
#include "RTClib.h"
//#include <U8g2lib.h>
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
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
//auto timer = timer_create_default();
RTC_DS3231 rtc;

// '00000250', 128x64px
const unsigned char reimuImage [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x04, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xc0, 0x00, 0x05, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xc0, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x1f, 0xfc, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x0f, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x01, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0x00, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xc0, 0x00, 0x38, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x00, 0x10, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
boolean button_down_now_state = HIGH;
boolean button_down_old_state = LOW;
boolean laser_state = HIGH;
boolean isRtc = true;

int pic = 0;
int maxPics = 4;

void setup() {
  
  Wire.begin();
  //Serial.begin(115200);
  //timer.every(9000, keypower);
  rtc.begin(); //starts rtc chip
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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
  display.setCursor(0,38);  display.print (" LASER TOGGLE");
  display.setCursor(0,47);  display.print (" ");
  display.setCursor(0,56);  display.print (" ");
  refresh();
}

if (pic == 2)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (">BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,38);  display.print (" LASER TOGGLE");
  display.setCursor(0,47);  display.print (" ");
  display.setCursor(0,56);  display.print (" ");
  refresh();
}

if (pic == 3)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (">EXECUTE ATTACK");
  display.setCursor(0,38);  display.print (" LASER TOGGLE");
  display.setCursor(0,47);  display.print (" ");
  display.setCursor(0,56);  display.print (" ");
  refresh();
}

if (pic == 4)
{
  header();
  display.setCursor(0,11);  display.print (" CLOCK");
  display.setCursor(0,20);  display.print (" BAD APPLE");
  display.setCursor(0,29);  display.print (" EXECUTE ATTACK");
  display.setCursor(0,38);  display.print (">LASER TOGGLE");
  display.setCursor(0,47);  display.print (" ");
  display.setCursor(0,56);  display.print (" ");
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
    else if(pic <= maxPics)
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
    else if(pic <= maxPics)
    {
      pic--;
    }
  }
}

if(digitalRead(BUTTON_CENTER)==LOW)
{
    if (pic == 1)
    {
      pic=0;
    }
    else if(pic == 2)
    {
      badApple();
    }
    else if(pic == 3)
    {
      badUSB();
    }
    else if(pic == 4)
    {
      laser();
    }
}


  
} //end loop

static const uint16_t Melody0[] PROGMEM = { 
        0b1110111101010011, 0b1111000101010101, 0b1110111101010110, 0b1111000101011000, 
        0b1111111101011010, 0b1110000101011010, 0b1110111101010011, 0b1111000101100001, 
        0b1111111101011010, 0b1110000101011010, 0b1111111101010011, 0b1110000101010011, 
        0b1110111101011010, 0b1111000101011000, 0b1110111101010110, 0b1111000101010101, 
        0b1110111101010011, 0b1111000101010101, 0b1110111101010110, 0b1111000101011000, 
        0b1111111101011010, 0b1110000101011010, 0b1110111101011000, 0b1111000101010110, 
        0b1110111101010101, 0b1111000101001010, 0b1110111101010101, 0b1111000101010110, 
        0b1110111101010101, 0b1111000101010011, 0b1110111101010010, 0b1111000101010101, 
        0b1110111101010011, 0b1111000101010101, 0b1110111101010110, 0b1111000101011000, 
        0b1111111101011010, 0b1110000101011010, 0b1110111101011000, 0b1111000101100001, 
        0b1111111101100011, 0b1111111101100011, 0b1111111101100011, 0b1100001101100011, 
        0b1111111101100101, 0b1110000101100101, 0b1111111101100110, 0b1110000101100110, 
        0b1110111101100011, 0b1111000101100101, 0b1110111101100110, 0b1111000101101000, 
        0b1111111101101010, 0b1110000101101010, 0b1110111101101000, 0b1111000101100110, 
        0b1111111101101000, 0b1110000101101000, 0b1111111101100101, 0b1110000101100101, 
        0b1111111101100110, 0b1110000101100110, 0b1111111101101000, 0b1110000101101000, 
        0b1111111101010011, 0b1111111101010011, 0b1111111101010011, 0b1111111101010011, 
        0b1011001101010011, 0b1111000101010101, 0b1111111101010110, 0b1110000101010110, 
        0b1111111101010101, 0b1111111101010101, 0b1101000101010101, 0b1111111101001010, 
        0b1111111101001010, 0b1101001101001010, 0b1111111101010101, 0b1111111101010101, 
        0b1111111101010101, 0b1100001101010101, 0b1110111101010110, 0b1111111101010011, 
        0b1111111101010011, 0b1101001101010011, 0b1111111101010001, 0b1111111101010001, 
        0b1111111101010001, 0b1100001101010001, 0b1110111101010011, 0b1111111101001010, 
        0b1111111101001010, 0b1101001101001010, 0b1111111101010011, 0b1111111101010011, 
        0b1111111101010011, 0b1111111101010011, 0b1111111101010011, 0b1111111101010011, 
  };
  
static const uint16_t Melody0_Length    = sizeof( Melody0 ) / sizeof(uint16_t);

void badApple()
{
      display.clearDisplay(); 
      display.drawBitmap(0, 0, reimuImage, 128, 64, WHITE); 
      display.display();
      uint8_t tempo = 1;
      playMelody_Data(Melody0, Melody0_Length, tempo); 
      noTone(BUZZER);
}

void playMelody_Data(const uint16_t MelodyData[], const uint16_t MelodyLength, const uint8_t tempo)
{
  // 8th Octave Frequencies C8 to B8, lower octaves are calculated from this
  static const uint16_t Freq8[] PROGMEM = { 4186 , 4435 , 4699  , 4978 , 5274 , 5588 , 5920 , 6272 , 6645 , 7040 , 7459 , 7902 };

  for(uint16_t  x = 0; x < MelodyLength; x++)
  {
    uint16_t data = pgm_read_word((uint16_t *)&MelodyData[x]);
    if((data & 0xF) == 0xF) 
    {
      noTone(BUZZER);
    }
    else
    {
      uint16_t Freq = pgm_read_word(&Freq8[data&0xF]) / ( 1 << (8-(data>>4 & 0xF)) );
      tone(BUZZER, Freq);    

    }    
    
    int16_t Duration = data>>8;
    while(Duration--) delay(tempo);
  }
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

void laser()
{
  //button_down_now_state = digitalRead (BUTTON_DOWN);
  //if (button_down_old_state == LOW && button_down_now_state == HIGH) {        //if low -> high
      laser_state = !laser_state;                        //switch state: true <-> false
      digitalWrite(LASER, laser_state);
  //button_down_old_state = button_down_now_state;       //save button state
      delay(500);
}

void badUSB()
{
  delay(00);
}
