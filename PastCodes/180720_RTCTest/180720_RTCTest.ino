// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
// RTC 라이브러리 사용을 위한 헤더파일 선언.
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;  // RTC 구조체 변수 선언

// 요일 이름 저장 배열
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void setup () 
{
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
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();   // 현재 날짜, 시간을 모듈에서 가져옵니다.
    
    Serial.print(now.year(), DEC);  // 년도 표시
    Serial.print('/');
    Serial.print(now.month(), DEC); // 월 표시
    Serial.print('/');
    Serial.print(now.day(), DEC);   // 일 표시
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  // 요일 표시
    Serial.print(") ");
    Serial.print(now.hour(), DEC);  // 시간 표시
    Serial.print(':');
    Serial.print(now.minute(), DEC);// 분 표시
    Serial.print(':');
    Serial.print(now.second(), DEC);// 초 표시
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = "); 
    Serial.print(now.unixtime()); // 1970년 1월1일 부터 현재까지를 초시간 가져오기
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L); // 현재까지의 지난 날짜 가져오기
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(1000);
}
