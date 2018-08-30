#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"
#define PIN 3
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(96, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_SEQUENCE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};

void setup() {
  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     rtc.adjust(DateTime(2018, 8, 14, 43, 0, 0));

  }
  
  matrix.begin();
  matrix.setTextWrap(0); // 0이면 안생기고 밀리고 , 1로하면 생기듯이 나옴
  matrix.setBrightness(30);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();


void loop() {
  DateTime now = rtc.now();
  DateTime future (now + TimeSpan(7,12,30,6));


  
  matrix.fillScreen(0); 
  matrix.setCursor(68, 0); 
  matrix.print(future.year());
  matrix.setCursor(36, 0);
  matrix.print(future.month());
  matrix.print(F("/"));
  matrix.print(future.day());
   matrix.setCursor(0, 0);
  matrix.print(future.hour());
  matrix.print(F(":"));
  matrix.print(future.minute());
  
  

  
  
matrix.setTextColor(colors[0]);
 
  matrix.show();
  delay(30);
}
