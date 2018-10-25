RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void rtcFunc(){
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
     rtc.adjust(DateTime(2018, 8, 15, 13, 40, 0));
  }
}

void rtcLed(){
  Serial.println("RTC Start!");
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
    Serial.println("RTC End");
}
