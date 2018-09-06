#include <Adafruit_NeoPixel.h>

#define PIN            3

#define PIXELS_ROWS 32
#define PIXELS_COLUMNS 24
#define PIXELS_COUNT 768 //PIXELS_ROWS * PIXELS_COLUMNS

#define ROW 7
#define COL 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIN, NEO_GRB + NEO_KHZ800);

int WinCheckField[ROW][COL];
boolean flag=0;
unsigned char e[8];
int globalRow;

uint32_t C0 = 0xFFFFFF; //White
uint32_t C1 = 0xFF0000; //Red
uint32_t C2 = 0x00FF00; //Green
uint32_t C3 = 0x0000FF; //Blue
uint32_t C4 = 0xFFFF00; //Yellow
uint32_t C5 = 0x00FFFF; //Cyan
uint32_t C6 = 0xFF00FF; //Magenta

uint32_t MyColors[7] = {C0, C1, C2, C3, C4, C5, C6}; //put the colors in an array

uint32_t color1 = MyColors[0];
uint32_t color2 = MyColors[5];

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
      pixels.show(); 
}

void clearPIXELS(){
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

void pixelarrayInit(){
  for(int i=0; i<ROW; i++) {
      for(int j=0; j<COL; j++) {
            WinCheckField[i][j] = 8;  
      }
      e[i] = 0x00;
  }
}

void showBlockcolor(int i, int j, uint32_t color){
  int cnt = 0;
  int ledarr[9] = {calcLED(i,j), calcLED(i,j+1), calcLED(i,j+2), calcLED(i+1,j), calcLED(i+1,j+1), calcLED(i+1,j+2), calcLED(i+2,j), calcLED(i+2,j+1), calcLED(i+2,j+2)};
  
  display_PixelColor(ledarr[cnt], color);
  display_PixelColor(ledarr[cnt+1], color);
  display_PixelColor(ledarr[cnt+2], color);
  display_PixelColor(ledarr[cnt+3], color);
  display_PixelColor(ledarr[cnt+4], color);
  display_PixelColor(ledarr[cnt+5], color);
  display_PixelColor(ledarr[cnt+6], color);
  display_PixelColor(ledarr[cnt+7], color);
  display_PixelColor(ledarr[cnt+8], color);
}

int enterROW(){
  Serial.println("enterROW Start");
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

void WinCheckField_Data(){
  Serial.println("WinCheckField_Data Start");
  int row = enterROW(); //globalRow;
  Serial.print("WinCheck row : ");
  Serial.println(row);
  int col = empty_check(row);
  Serial.print(" col ?:");
  Serial.println(col); 
  if(col<6){
   if(flag == 0) flag = 1; else flag = 0;}
  Serial.print("WinCheck col : ");
  Serial.println(col);
  Serial.print("Before WinCheckField[row][col] : ");
  Serial.println(WinCheckField[row][col]);
  if(col != 0x1F && WinCheckField[row][col] == 8) {
    WinCheckField[row][col] = flag;
    Serial.print("After WinCheckField[row][col] : ");
    Serial.println(WinCheckField[row][col]);
    if(WinCheckField[row][col] == 1){
      showBlockcolor(4*row+1, 4*col+1, color1);
    }
    else{
      showBlockcolor(4*row+1, 4*col+1, color2);
    }
    
    if(col > 4){
      Serial.print("Row");
      Serial.print(row);
      Serial.println(" is FULL! Enter other Row");
      enterROW();
    }
    else col = e[row]++;
    
    if(row == 0) e1++;
    else if(row == 1) e2++;
    else if(row == 2) e3++;
    else if(row == 3) e4++;
    else if(row == 4) e5++;
    else if(row == 5) e6++;
    else if(row == 6) e7++;
  } else {
    //WinCheckField_Data();
  }
}

int empty_check(int i) {
  return e[i];
}

void blockBlink(){
  Serial.println("******************");
  Serial.println("blockBlink Start");
  globalRow = enterROW();
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
    //clearPIXELS();
  }
  }
  Serial.println("blockBlink END");
}

void fieldON(){
  Serial.println("fieldON Start");
  int i;
  int j;
  
  for(i=1; i<=7; i++)
    for(j=0; j<=6; j++){
        if(WinCheckField_Data[i][j] == 0)
          showBlockcolor(4*i+1, 4*j+1, color1);
        else if(WinCheckField_Data[i][j] == 1)
          showBlockcolor(4*i+1, 4*j+1, color2);
    }
  Serial.println("fieldON End");
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

  pixelarrayInit();
}

void loop() {
  //blockBlink();
  //clearPIXELS();
  WinCheckField_Data();
  //fieldON();
}
