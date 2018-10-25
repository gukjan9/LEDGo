#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>
#include <Wire.h>
#include "RTClib.h"

#define PIN            3

#define PIXELS_ROWS 32
#define PIXELS_COLUMNS 24
#define PIXELS_COUNT 768 //PIXELS_ROWS * PIXELS_COLUMNS

#define ROW 7
#define COL 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(96, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_SEQUENCE,
  NEO_GRB            + NEO_KHZ800);

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};
int x = matrix.width();

int WinCheckField[ROW][COL];
boolean flag=0;
unsigned char e[8];
int globalRow;

int gamestatus = 0;

int player1 = 0;
int player2 = 0;

uint32_t C0 = 0xFFFFFF; //White
uint32_t C1 = 0xFF0000; //Red
uint32_t C2 = 0x00FF00; //Green
uint32_t C3 = 0x0000FF; //Blue
uint32_t C4 = 0xFFFF00; //Yellow
uint32_t C5 = 0x00FFFF; //Cyan
uint32_t C6 = 0xFF00FF; //Magenta

uint32_t MyColors[7] = {C0, C1, C2, C3, C4, C5, C6}; //put the colors in an array

uint32_t color2 = MyColors[1];
uint32_t color1 = MyColors[2];
uint32_t color3 = MyColors[6];

const int buttonPin1 = 22;
const int buttonPin2 = 24;
const int buttonPin3 = 26;
const int buttonPin4 = 28;
const int buttonPin5 = 30;
const int buttonPin6 = 32;
const int buttonPin7 = 34;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
int buttonState7 = 0;

int bt1 = 0;
int bt2 = 0;
int bt3 = 0;
int bt4 = 0;
int bt5 = 0;
int bt6 = 0;
int bt7 = 0;

int e1 = 0;
int e2 = 0;
int e3 = 0;
int e4 = 0;
int e5 = 0;
int e6 = 0;
int e7 = 0;

void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      pixels.setPixelColor(led+768, color);
      pixels.show();
}

void clearPIXELS(){
  Serial.println("Clearing Pixels...");
  
  for (int i=0; i<PIXELS_COUNT; i++){
    pixels.setPixelColor(i, 0);
  }
}

int calcLED(int row, int col){
  int odd = row%2;
  int led = 0;

  if(odd){
    if(col >= 1 && col <= 8){
      led = 8*row - col;
      return led;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row - col + 264;
      return led;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row - col + 528;
      return led;
    }
  }
  else{
    if(col >= 1 && col <= 8){
      led = 8*row + col - 9;
      return led;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row + col - 9 + 248;
      return led;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row + col - 9 + 496;
      return led;
    }
  }
}

int Quotient(int x, int y){               // 몫 함수
  int q = x / y;
  
  return q;
}

int Remainder(int x, int y){              // 나머지 함수
  int r = x % y;

  return r;
}

void display_5bit(int data, int textRow, int textCol){              // ■■■■■ 구현
  int division = 16;
  
  while(division != 0){
    int valBit = data & division;

    if(valBit == 0) valBit = 0;
    else valBit = 1;
 
    if(division == 0x10) display_PixelColor(calcLED((5+textRow)*valBit, textCol*valBit), color1);             // (6*textRow) -> 1줄에 5글자일때 일정간격 띄운것
    else if(division == 0x08) display_PixelColor(calcLED((4+textRow)*valBit, textCol*valBit), color1);
    else if(division == 0x04) display_PixelColor(calcLED((3+textRow)*valBit, textCol*valBit), color1);
    else if(division == 0x02) display_PixelColor(calcLED((2+textRow)*valBit, textCol*valBit), color1);
    else if(division == 0x01) display_PixelColor(calcLED((1+textRow)*valBit, textCol*valBit), color1);
    division = division / 2;
  }
}

void display_PixelHex(int hex, int textRow, int textCol){             // hex값에 따라 ■■■■■ 구현
  int quotient = hex;
  int data = 0x00;
  
  while(quotient != 0){
    int temp_remainder = Remainder(quotient, 2);
    data = temp_remainder | data;
    data = data << 1;
    quotient = Quotient(quotient, 2);
  }
  display_5bit(hex, textRow, textCol);
}

void display_Alphabet(char alphabet, int textRow, int textCol){           // Alphabet 정의  
  int Alphabet[44][7] = 
  {{0X0E, 0X11, 0X11, 0X11, 0X11, 0X11, 0X0E}, // 0
  {0X1F, 0X04, 0X04, 0X04, 0X05, 0X06, 0X04},
  {0X1F, 0X06, 0X0C, 0X18, 0X11, 0X13, 0X0E},
  {0X0F, 0X10, 0X10, 0X0F, 0X10, 0X10, 0X0F},
  {0X08, 0X08, 0X1F, 0X09, 0X09, 0X09, 0X09},
  {0X0E, 0X11, 0X10, 0X10, 0X0F, 0X01, 0X1F},
  {0X0E, 0X11, 0X11, 0X0F, 0X01, 0X01, 0X0E},
  {0X10, 0X10, 0X10, 0X10, 0X11, 0X11, 0X1F},
  {0X0E, 0X11, 0X11, 0X1F, 0X11, 0X11, 0X0E},
  {0X0E, 0X10 ,0X10, 0X1F, 0X11, 0X11, 0X0E}, // 9
  {},{},{},{},{},{},{},
  {0x11, 0x11, 0x11, 0x1F, 0x11, 0x0A, 0x04}, // A
  {0x0F, 0x11, 0x11, 0x0F, 0x11, 0x11, 0x0F}, 
  {0X1E, 0X01, 0X01, 0X01, 0X01, 0X01, 0X1E}, 
  {0X0F, 0X11, 0X11, 0X11, 0X11, 0X11, 0X0F}, 
  {0X1F, 0X01, 0X01, 0X1F, 0X01, 0X01, 0X1F}, 
  {0X01, 0X01, 0X01, 0X1F, 0X01, 0X01, 0X1F}, // F
  {0X1E, 0X11, 0X11, 0X1D, 0X01, 0X01, 0X1E}, 
  {0X11, 0X11, 0X11, 0X1F, 0X11, 0X11, 0X11}, 
  {0X1F, 0X04, 0X04, 0X04, 0X04, 0X04, 0X1F}, 
  {0X06, 0X09, 0X08, 0X08, 0X08, 0X08, 0X1F}, 
  {0X11, 0X09, 0X05, 0X03, 0X05, 0X09, 0X11}, 
  {0X1F, 0X01, 0X01, 0X01, 0X01, 0X01, 0X01}, // L
  {0X11, 0X11, 0X11, 0X11, 0X15, 0X1B, 0X11}, 
  {0X11, 0X19, 0X19, 0X15, 0X13, 0X13, 0X11}, 
  {0X0E, 0X11, 0X11, 0X11, 0X11, 0X11, 0X0E}, 
  {0X01, 0X01, 0X01, 0X0F, 0X11, 0X11, 0X0F}, 
  {0x10, 0x0E, 0x15, 0x11, 0x11, 0x11, 0x0E}, // Q
  {0X11, 0X11, 0X11, 0X0F, 0X11, 0X11, 0X0F}, 
  {0X0E, 0X11, 0X10, 0X0E, 0X01, 0X11, 0X0E}, 
  {0X04, 0X04, 0X04, 0X04, 0X04, 0X04, 0X1F}, 
  {0X0E, 0X11, 0X11, 0X11, 0X11, 0X11, 0X11}, 
  {0X04, 0X0A, 0X11, 0X11, 0X11, 0X11, 0X11}, // V
  {0X0A, 0X15, 0X15, 0X15, 0X11, 0X11, 0X11}, 
  {0X11, 0X11, 0X0A, 0X04, 0X0A, 0X11, 0X11}, 
  {0X04, 0X04, 0X04, 0X0A, 0X0A, 0X11, 0X11}, 
  {0X1F, 0X03, 0X02, 0X04, 0X08, 0X18, 0X1F}}; // Z

  int ascii = alphabet;
  
  display_PixelHex(Alphabet[ascii - 48][0], textRow, 1+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][1], textRow, 2+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][2], textRow, 3+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][3], textRow, 4+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][4], textRow, 5+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][5], textRow, 6+(textCol*8));
  display_PixelHex(Alphabet[ascii - 48][6], textRow, 7+(textCol*8));
}

void pixelarrayInit(){                    // Wincheck값 초기화
  for(int i=0; i<ROW; i++) {
      for(int j=0; j<COL; j++) {
            WinCheckField[i][j] = 8;  
      }
      e[i] = 0x00;
  }
}

void showBlockcolor(int i, int j, uint32_t color){
  int ledarr[9] = {calcLED(i,j), calcLED(i,j+1), calcLED(i,j+2), calcLED(i+1,j), calcLED(i+1,j+1), calcLED(i+1,j+2), calcLED(i+2,j), calcLED(i+2,j+1), calcLED(i+2,j+2)};
  
  display_PixelColor(ledarr[0], color);
  display_PixelColor(ledarr[1], color);
  display_PixelColor(ledarr[2], color);
  display_PixelColor(ledarr[3], color);
  display_PixelColor(ledarr[4], color);
  display_PixelColor(ledarr[5], color);
  display_PixelColor(ledarr[6], color);
  display_PixelColor(ledarr[7], color);
  display_PixelColor(ledarr[8], color);
}

int enterRow(){
  Serial.println("enterRow Start");
  int buttoni;
  
  bt1 = digitalRead(buttonPin1);
  bt2 = digitalRead(buttonPin2);
  bt3 = digitalRead(buttonPin3);
  bt4 = digitalRead(buttonPin4);
  bt5 = digitalRead(buttonPin5);
  bt6 = digitalRead(buttonPin6);
  bt7 = digitalRead(buttonPin7);

  while(1){
    buttonState1=digitalRead(buttonPin1);
    buttonState2=digitalRead(buttonPin2);
    buttonState3=digitalRead(buttonPin3);
    buttonState4=digitalRead(buttonPin4);
    buttonState5=digitalRead(buttonPin5);
    buttonState6=digitalRead(buttonPin6);
    buttonState7=digitalRead(buttonPin7);

  if(bt1 !=0 && buttonState1==0){
    Serial.println("Button1 Pressed");
    buttoni=0;
    return buttoni;
   }
   else if(bt2 !=0 && buttonState2==0){
    Serial.println("Button2 Pressed");
    buttoni=1;
    return buttoni;
   }
   else if(bt3 !=0 && buttonState3==0){
    Serial.println("Button3 Pressed");
    buttoni=2;
    return buttoni;
   }
   else if(bt4 !=0 && buttonState4==0){
    Serial.println("Button4 Pressed");
    buttoni=3;
    return buttoni;
   }
   else if(bt5 !=0 && buttonState5==0){
    Serial.println("Button5 Pressed");
    buttoni=4;
    return buttoni;
   }
   else if(bt6 !=0 && buttonState6==0){
    Serial.println("Button6 Pressed");
    buttoni=5;
    return buttoni;
   }
   else if(bt7 !=0 && buttonState7==0){
    Serial.println("Button7 Pressed");
    buttoni=6;
    return buttoni;
   }

   bt1=buttonState1;
   bt2=buttonState2;
   bt3=buttonState3;
   bt4=buttonState4;
   bt5=buttonState5;
   bt6=buttonState6;
   bt7=buttonState7;
  }
}

void display_Firework(int i){
  int j;
  for(j=1; j<=12; j++){
    display_PixelColor(calcLED(i+3,j), color3);
    delay(70);
    display_PixelColor(calcLED(i+3,j), 0);
  }
  display_PixelColor(calcLED(i+3,12), color3);
  display_PixelColor(calcLED(i+2,13), color3);
  display_PixelColor(calcLED(i+4,13), color3);
  display_PixelColor(calcLED(i+2,11), color3);
  display_PixelColor(calcLED(i+4,11), color3);
  delay(100);
  display_PixelColor(calcLED(i+3,12), 0);
  display_PixelColor(calcLED(i+2,13), 0);
  display_PixelColor(calcLED(i+4,13), 0);
  display_PixelColor(calcLED(i+2,11), 0);
  display_PixelColor(calcLED(i+4,11), 0);
  delay(100);
  display_PixelColor(calcLED(i+3,13), color3);
  display_PixelColor(calcLED(i+3,14), color3);
  display_PixelColor(calcLED(i+4,12), color3);
  display_PixelColor(calcLED(i+5,12), color3);
  display_PixelColor(calcLED(i+3,10), color3);
  display_PixelColor(calcLED(i+3,11), color3);
  display_PixelColor(calcLED(i+1,12), color3);
  display_PixelColor(calcLED(i+2,12), color3);
  delay(100);
  display_PixelColor(calcLED(i+3,13), 0);
  display_PixelColor(calcLED(i+3,14), 0);
  display_PixelColor(calcLED(i+4,12), 0);
  display_PixelColor(calcLED(i+5,12), 0);
  display_PixelColor(calcLED(i+3,10), 0);
  display_PixelColor(calcLED(i+3,11), 0);
  display_PixelColor(calcLED(i+1,12), 0);
  display_PixelColor(calcLED(i+2,12), 0);
  delay(100);
}

void display_LEDGo(){
  Serial.println("Welcome to LEDGo!");
  display_Firework(2);
  display_Alphabet('L', 2, 1);
  display_Firework(8);
  display_Alphabet('E', 8, 1);
  display_Firework(14);
  display_Alphabet('D', 14, 1);
  display_Firework(20);
  display_Alphabet('G', 20, 1);
  display_Firework(26);
  display_Alphabet('O', 26, 1);
}

void display_PressAnyKey(){
  Serial.println("Press Any Key to Start");
  display_Alphabet('P', 2, 2);
  display_Alphabet('R', 8, 2);
  display_Alphabet('E', 14, 2);
  display_Alphabet('S', 20, 2);
  display_Alphabet('S', 26, 2);

  display_Alphabet('A', 8, 1);
  display_Alphabet('N', 14, 1);
  display_Alphabet('Y', 20, 1);

  display_Alphabet('K', 8, 0);
  display_Alphabet('E', 14, 0);
  display_Alphabet('Y', 20, 0);
}

void display_StartingScreen(){                  // 오프닝 화면
  int lux;
  pixels.setBrightness(20);
  display_LEDGo();
  Serial.println("Dimming Brightness");
  for(lux = 20; lux >= 0; lux--){
    Serial.print("Lux : ");
    Serial.println(lux);
    pixels.setBrightness(lux);
    pixels.show();
    delay(70);
  }
  pixels.setBrightness(20);
  display_PressAnyKey();
  Serial.println("Dimming Brightness");
  for(lux = 20; lux >= 0; lux--){
    Serial.print("Lux : ");
    Serial.println(lux);
    pixels.setBrightness(lux);
    pixels.show();
    delay(70);
  }
}

void displayPlayer(int player){
  Serial.print("Waiting for Player ");
  Serial.println(player);
  display_Alphabet('P', 0, 2);
  display_Alphabet('L', 6, 2);
  display_Alphabet('A', 12, 2);
  display_Alphabet('Y', 18, 2);
  display_Alphabet('E', 24, 2);

  display_Alphabet('1', 12, 1);
}

void displayReady(int player){
  Serial.print("Player ");
  Serial.print(player);
  Serial.println(" is Ready !");
  display_Alphabet('R', 0, 0);
  display_Alphabet('E', 6, 0);
  display_Alphabet('A', 12, 0);
  display_Alphabet('D', 18, 0);
  display_Alphabet('Y', 24, 0);
}

void enterPlayer(){
  Serial.println("enterPlayer Start");
  int val = enterRow();

  if(val == 0 | val == 6){
    if(val == 0 && player1 == 0){
      player1 = 1;
      displayReady(1);
      if(player2 == 0) enterPlayer();
     }
   else if(val == 6 && player2 == 0){
      player2 = 1;
      displayReady(2);
      if(player1 == 0) enterPlayer();
     }
   }
   else enterPlayer();

  if(player1 == 1 && player2 == 1){
    Serial.println("GAME START !");
    gamestatus = 2;
    clearPIXELS();
  }
  else enterPlayer();
}

int empty_check(int i) {
  return e[i];
}

void right_1(){                        //우3
  int a = globalRow;
  int b = empty_check(a);
  int A = globalRow;
  int cnt = 0;
  
  for(; a<=A+3; a++){
    if(WinCheckField[a][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      Serial.println("right_1 WinCheck LED Blink");
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*b+1, color3);
      showBlockcolor(4*(a+2)+1, 4*b+1, color3);
      showBlockcolor(4*(a+3)+1, 4*b+1, color3);
    }
}

void right_2(){                      //좌1우2
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++){
    if(WinCheckField[a-1][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      Serial.println("right_2 WinCheck LED Blink");
      showBlockcolor(4*(a-1)+1, 4*b+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*b+1, color3);
      showBlockcolor(4*(a+2)+1, 4*b+1, color3);
   }
}

void right_3(){                      //좌2우1
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++){
    if(WinCheckField[a-2][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      Serial.println("right_3 WinCheck LED Blink");
      showBlockcolor(4*(a-2)+1, 4*b+1, color3);
      showBlockcolor(4*(a-1)+1, 4*b+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*b+1, color3);
   }
}

void right_4(){                      //좌3
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++){
    if(WinCheckField[a-3][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      Serial.println("right_4 WinCheck LED Blink");
      showBlockcolor(4*(a-3)+1, 4*b+1, color3);
      showBlockcolor(4*(a-2)+1, 4*b+1, color3);
      showBlockcolor(4*(a-1)+1, 4*b+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
   }
}

void bottom(){                       //하3
  int a = globalRow;
  int b = empty_check(a);
  int B = b;
  int cnt = 0;
  
  for(; b<=B+3; b++){
    if(WinCheckField[a][b-3]==flag) cnt++;
    }
    if(cnt==4){
      b = b-4;
      Serial.println("bottom WinCheck LED Blink");
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*a+1, 4*(b-1)+1, color3);
      showBlockcolor(4*a+1, 4*(b-2)+1, color3);
      showBlockcolor(4*a+1, 4*(b-3)+1, color3);
   }
}

void r_upcross_1(){                    //우상3
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++,b++){
    if(WinCheckField[a][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b-4;
      Serial.println("r_upcross_1 WinCheck LED Blink");
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b+1)+1, color3);
      showBlockcolor(4*(a+2)+1, 4*(b+2)+1, color3);
      showBlockcolor(4*(a+3)+1, 4*(b+3)+1, color3);
   }
}

void r_upcross_2(){                  //좌하1우상2
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
    for(; a<=A+3; a++,b++){
    if(WinCheckField[a-1][b-1]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b-4;
      Serial.println("r_upcross_2 WinCheck LED Blink");
      showBlockcolor(4*(a-1)+1, 4*(b-1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b+1)+1, color3);
      showBlockcolor(4*(a+2)+1, 4*(b+2)+1, color3);
   }
}

void r_upcross_3(){                  //좌하2우상1
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
    for(; a<=A+3; a++,b++){
    if(WinCheckField[a-2][b-2]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b-4;
      Serial.println("r_upcross_3 WinCheck LED Blink");
      showBlockcolor(4*(a-2)+1, 4*(b-2)+1, color3);
      showBlockcolor(4*(a-1)+1, 4*(b-1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b+1)+1, color3);
   }
}

void r_upcross_4(){                  //좌하3
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
    for(; a<=A+3; a++,b++){
    if(WinCheckField[a-3][b-3]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b-4;
      Serial.println("r_upcross_4 WinCheck LED Blink");
      showBlockcolor(4*(a-3)+1, 4*(b-3)+1, color3);
      showBlockcolor(4*(a-2)+1, 4*(b-2)+1, color3);
      showBlockcolor(4*(a-1)+1, 4*(b-1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
   }
}

void r_downcross_1(){                  //우하3
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
    for(; a<=A+3; a++,b--){
    if(WinCheckField[a][b]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b+4;
      Serial.println("r_downcross_1 WinCheck LED Blink");
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b-1)+1, color3);
      showBlockcolor(4*(a+2)+1, 4*(b-2)+1, color3);
      showBlockcolor(4*(a+3)+1, 4*(b-3)+1, color3);
   }
}

void r_downcross_2(){                //좌상1우하2
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++,b--){
    if(WinCheckField[a-1][b+1]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b+4;
      Serial.println("r_downcross_2 WinCheck LED Blink");
      showBlockcolor(4*(a-1)+1, 4*(b+1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b-1)+1, color3);
      showBlockcolor(4*(a+2)+1, 4*(b-2)+1, color3);
  }
}

void r_downcross_3(){                //좌상2우하1
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++,b--){
    if(WinCheckField[a-2][b+2]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b+4;
      Serial.println("r_downcross_3 WinCheck LED Blink");
      showBlockcolor(4*(a-2)+1, 4*(b+2)+1, color3);
      showBlockcolor(4*(a-1)+1, 4*(b+1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
      showBlockcolor(4*(a+1)+1, 4*(b-1)+1, color3);
  }
}

void r_downcross_4(){                //좌상3
  int a = globalRow;
  int b = empty_check(a);
  int A = a;
  int cnt = 0;
  
  for(; a<=A+3; a++,b--){
    if(WinCheckField[a-3][b+3]==flag) cnt++;
    }
    if(cnt==4){
      a = a-4;
      b = b+4; 
      Serial.println("r_downcross_4 WinCheck LED Blink");
      showBlockcolor(4*(a-3)+1, 4*(b+3)+1, color3);
      showBlockcolor(4*(a-2)+1, 4*(b+2)+1, color3);
      showBlockcolor(4*(a-1)+1, 4*(b+1)+1, color3);
      showBlockcolor(4*a+1, 4*b+1, color3);
   }
}

void wincheck(){
  Serial.println("WinCheck Start!");
  
  int globalCol = empty_check(globalRow);
  
  if(globalRow == 0 && globalCol >= 0 && globalCol <= 2){                               // (1,1) ~ (1,3)
    right_1();
    r_upcross_1();
  }
  else if(globalRow == 0 && globalCol >= 3 && globalCol <= 5){        // (1,4) ~ (1,6)
    right_1();
    bottom();
    r_downcross_1();
  }
  else if(globalRow == 1 && globalCol == 0){
    right_1();
    right_2();
    r_upcross_1();
  }
  else if(globalRow == 1 && globalCol == 1){
    right_1();
    right_2();
    r_upcross_1();
    r_upcross_2();
  }
  else if(globalRow == 1 && globalCol == 2){
    right_1();
    right_2();
    r_upcross_1();
    r_upcross_2();
    r_downcross_2();
  }
  else if(globalRow == 1 && globalCol == 3){
    right_1();
    right_2();
    bottom();
    r_upcross_2();
    r_downcross_1();
    r_downcross_2();
  }
  else if(globalRow == 1 && globalCol == 4){
    right_1();
    right_2();
    bottom();
    r_downcross_1();
    r_downcross_2();
  }
  else if(globalRow == 1 && globalCol == 5){
    right_1();
    right_2();
    bottom();
    r_downcross_1();
  }
  else if(globalRow == 2 && globalCol == 0){
    right_1();
    right_2();
    right_3();
    r_upcross_1();
  }
  else if(globalRow == 2 && globalCol == 1){
    right_1();
    right_2();
    right_3();
    r_upcross_1();
    r_upcross_2();
    r_downcross_3();
  }
  else if(globalRow == 2 && globalCol == 2){
    right_1();
    right_2();
    right_3();
    r_upcross_1();
    r_upcross_2();
    r_upcross_3();
    r_downcross_2();
    r_downcross_3();
  }
  else if(globalRow == 2 && globalCol == 3){
    right_1();
    right_2();
    right_3();
    bottom();
    r_upcross_2();
    r_upcross_3();
    r_downcross_1();
    r_downcross_2();
    r_downcross_3();
  }
  else if(globalRow == 2 && globalCol == 4){
    right_1();
    right_2();
    right_3();
    bottom();
    r_upcross_3();
    r_downcross_1();
    r_downcross_2();
  }
  else if(globalRow == 2 && globalCol == 5){
    right_1();
    right_2();
    right_3();
    bottom();
    r_downcross_1();
  }
  else if(globalRow == 3 && globalCol == 0){
    right_1();
    right_2();
    right_3();
    right_4();
    r_upcross_1();
    r_downcross_4();
  }
  else if(globalRow == 3 && globalCol == 1){
    right_1();
    right_2();
    right_3();
    right_4();
    r_upcross_1();
    r_upcross_2();
    r_downcross_3();
    r_downcross_4();
  }
  else if(globalRow == 3 && globalCol == 2){
    right_1();
    right_2();
    right_3();
    right_4();
    r_upcross_1();
    r_upcross_2();
    r_upcross_3();
  }
  else if(globalRow == 3 && globalCol == 3){
    right_1();
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_1();
    r_upcross_2();
    r_upcross_3();
    r_upcross_4();
    r_downcross_1();
    r_downcross_2();
    r_downcross_3();
  }
  else if(globalRow == 3 && globalCol == 4){
    right_1();
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_3();
    r_upcross_4();
    r_downcross_1();
    r_downcross_2();
  }
  else if(globalRow == 3 && globalCol == 5){
    right_1();
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_4();
    r_downcross_1();
  }
  else if(globalRow == 4 && globalCol == 0){
    right_2();
    right_3();
    right_4();
    r_downcross_4();
  }
  else if(globalRow == 4 && globalCol == 1){
    right_2();
    right_3();
    right_4();
    r_upcross_2();
    r_downcross_3();
    r_downcross_4();
  }
  else if(globalRow == 4 && globalCol == 2){
    right_2();
    right_3();
    right_4();
    r_upcross_2();
    r_upcross_3();
    r_downcross_2();
    r_downcross_3();
    r_downcross_4();
  }
  else if(globalRow == 4 && globalCol == 3){
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_2();
    r_upcross_3();
    r_upcross_4();
    r_downcross_2();
    r_downcross_3();
  }
  else if(globalRow == 4 && globalCol == 4){
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_3();
    r_upcross_4();
    r_downcross_2();
  }
  else if(globalRow == 4 && globalCol == 5){
    right_2();
    right_3();
    right_4();
    bottom();
    r_upcross_4();
  }
  else if(globalRow == 5 && globalCol == 0){
    right_3();
    right_4();
    r_downcross_4();
  }
  else if(globalRow == 5 && globalCol == 1){
    right_3();
    right_4();
    r_downcross_3();
    r_downcross_4();
  }
  else if(globalRow == 5 && globalCol == 2){
    right_3();
    right_4();
    r_upcross_3();
    r_downcross_3();
    r_downcross_4();
  }
  else if(globalRow == 5 && globalCol == 3){
    right_3();
    right_4();
    bottom();
    r_upcross_3();
    r_upcross_4();
    r_downcross_3();
  }
  else if(globalRow == 5 && globalCol == 4){
    right_3();
    right_4();
    bottom();
    r_upcross_3();
    r_upcross_4();
  }
  else if(globalRow == 5 && globalCol == 6){
    right_3();
    right_4();
    bottom();
    r_upcross_4();
  }
  else if(globalRow == 6 && globalCol >= 0 && globalCol <= 2){
    right_4();
    r_downcross_4();
  }
  else if(globalRow == 6 && globalCol >= 3 && globalCol <= 5){
    right_4();
    bottom();
    r_upcross_4();
  }
  Serial.println("WinCheck End");
}

void WinCheckField_Data(){
  Serial.println("WinCheckField_Data Start");
  int row = globalRow;
  Serial.print("WinCheck row : ");
  Serial.println(row);
  int col = empty_check(row);
    
  if(flag == 0) flag = 1; else flag = 0;
  Serial.print("WinCheck col : ");
  Serial.println(col);
  Serial.print("Before WinCheckField[row][col] : ");
  Serial.println(WinCheckField[row][col]);
  if(col != 0x1F && WinCheckField[row][col] == 8) {
    WinCheckField[row][col] = flag;
    Serial.print("After WinCheckField[row][col] : ");
    Serial.println(WinCheckField[row][col]);
    if(WinCheckField[row][col] == 1) showBlockcolor(4*row+1, 4*col+1, color1);
    else showBlockcolor(4*row+1, 4*col+1, color2);
    }

    wincheck();
    
    col = e[row]++;
    
    if(row == 0) e1++;
    else if(row == 1) e2++;
    else if(row == 2) e3++;
    else if(row == 3) e4++;
    else if(row == 4) e5++;
    else if(row == 5) e6++;
    else if(row == 6) e7++;
    else {
    //WinCheckField_Data();
  }
}

void blockBlink(){
  Serial.println("******************");
  Serial.println("blockBlink Start");
  globalRow = enterRow();
  int i = globalRow;
  int j;
  int top = 21;

  if(i == 0) j = e1;
  else if(i == 1) j = e2;
  else if(i == 2) j = e3;
  else if(i == 3) j = e4;
  else if(i == 4) j = e5;
  else if(i == 5) j = e6;
  else if(i == 6) j = e7;

  if(j > 5){
      Serial.print("Row");
      Serial.print(globalRow);
      Serial.println(" is FULL! Enter other Row");
      blockBlink();
    }

  if(flag == 0){
  while(top >= 4*j+1){
    showBlockcolor(4*i+1, top, color1);
    delay(100);
    if(top > 4*j+1) showBlockcolor(4*i+1, top, 0);
    top = top - 4;
  }
  }
  else{
    while(top >= 4*j+1){
    showBlockcolor(4*i+1, top, color2);
    delay(100);
    if(top > 4*j+1) showBlockcolor(4*i+1, top, 0);
    top = top - 4;
  }
  }
  Serial.println("blockBlink END");
}

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

boolean mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

void enterAnyKey(){
  Serial.println("enterAnyKey Start");
  int switchState = digitalRead (buttonPin1) | digitalRead (buttonPin2) | digitalRead (buttonPin3) 
                  | digitalRead (buttonPin4) | digitalRead (buttonPin5) | digitalRead (buttonPin6)| digitalRead (buttonPin7); // Press Any Key
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      Serial.println("Button Pressed");
      mouseIsActive = !mouseIsActive;
    }
  }
  if ( mouseIsActive ) {
      gamestatus = 1;
    }
  lastSwitchState = switchState;
}

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);

  rtcFunc();

  if(gamestatus == 0){
    MsTimer2::set(100, enterAnyKey);
    MsTimer2::start();
  }

  /* if(gamestatus == 1){
    MsTimer2::set(1000, setTime);
    MsTimer2::start();
  } */

  pixelarrayInit();
}

void loop() {
  if(gamestatus == -1) rtcLed();

  else if(gamestatus == 0){
    display_StartingScreen();
    MsTimer2::stop();
  }
  
  else if(gamestatus == 1){
    displayPlayer(1);
    enterPlayer();
  }
    
  else if(gamestatus == 2){
    blockBlink();
    WinCheckField_Data();
  }
}
