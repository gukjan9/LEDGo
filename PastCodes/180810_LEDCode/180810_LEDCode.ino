#include <Adafruit_NeoPixel.h>

#define PIN            3

#define PIXELS_ROWS 32
#define PIXELS_COLUMNS 24
#define PIXELS_COUNT 768 //PIXELS_ROWS * PIXELS_COLUMNS

#define ROW 7
#define COL 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIN, NEO_GRB + NEO_KHZ800);

int WinCheckField[COL][ROW];
boolean flag=0;
unsigned char e[8];

uint32_t C0 = 0x000000; //Black
uint32_t C1 = 0xFFFFFF; //White
uint32_t C2 = 0xFF0000; //Red
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x0000FF; //Blue
uint32_t C5 = 0xFFFF00; //Yellow
uint32_t C6 = 0x00FFFF; //Cyan
uint32_t C7 = 0xFF00FF; //Magenta
uint32_t C8 = 0x800000; //Maroon
uint32_t C9 = 0x808000; //Olive
uint32_t C10 = 0x800080; //Purple
uint32_t C11 = 0x008080; //Teal

uint32_t MyColors[12] = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11}; //put the colors in an array

uint32_t color1 = MyColors[3];
uint32_t color2 = MyColors[4];

const int buttonPin1 = 22;    

int buttonState1 = 0;  

int bt1=0;

void display_PixelColor(int led, uint32_t color) {
  /* int row;
  int col;
      led = calcLED(row, col); */
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

void pixelarraySetup(){
  for(int i=0; i<COL; i++) {
      for(int j=0;j<ROW;j++) {
            WinCheckField[i][j] = 8;  
      }
      e[i] = 0x00;
  }
}

void showBlock(int i){
  int cnt = 0;
  int ledarr[9] = {calcLED(i,i), calcLED(i,i+1), calcLED(i,i+2), calcLED(i+1,i), calcLED(i+1,i+1), calcLED(i+1,i+2), calcLED(i+2,i), calcLED(i+2,i+1), calcLED(i+2,i+2)};
  
  display_PixelColor(ledarr[cnt], color1);
  display_PixelColor(ledarr[cnt+1], color1);
  display_PixelColor(ledarr[cnt+2], color1);
  display_PixelColor(ledarr[cnt+3], color1);
  display_PixelColor(ledarr[cnt+4], color1);
  display_PixelColor(ledarr[cnt+5], color1);
  display_PixelColor(ledarr[cnt+6], color1);
  display_PixelColor(ledarr[cnt+7], color1);
  display_PixelColor(ledarr[cnt+8], color1);
}

void showBlockcolor1(int i, int j){
  int cnt = 0;
  int ledarr[9] = {calcLED(i,j), calcLED(i,j+1), calcLED(i,j+2), calcLED(i+1,j), calcLED(i+1,j+1), calcLED(i+1,j+2), calcLED(i+2,j), calcLED(i+2,j+1), calcLED(i+2,j+2)};
  
  display_PixelColor(ledarr[cnt], color1);
  display_PixelColor(ledarr[cnt+1], color1);
  display_PixelColor(ledarr[cnt+2], color1);
  display_PixelColor(ledarr[cnt+3], color1);
  display_PixelColor(ledarr[cnt+4], color1);
  display_PixelColor(ledarr[cnt+5], color1);
  display_PixelColor(ledarr[cnt+6], color1);
  display_PixelColor(ledarr[cnt+7], color1);
  display_PixelColor(ledarr[cnt+8], color1);
}

void showBlockcolor2(int i, int j){
  int cnt = 0;
  int ledarr[9] = {calcLED(i,j), calcLED(i,j+1), calcLED(i,j+2), calcLED(i+1,j), calcLED(i+1,j+1), calcLED(i+1,j+2), calcLED(i+2,j), calcLED(i+2,j+1), calcLED(i+2,j+2)};
  
  display_PixelColor(ledarr[cnt], color2);
  display_PixelColor(ledarr[cnt+1], color2);
  display_PixelColor(ledarr[cnt+2], color2);
  display_PixelColor(ledarr[cnt+3], color2);
  display_PixelColor(ledarr[cnt+4], color2);
  display_PixelColor(ledarr[cnt+5], color2);
  display_PixelColor(ledarr[cnt+6], color2);
  display_PixelColor(ledarr[cnt+7], color2);
  display_PixelColor(ledarr[cnt+8], color2);
}

int enterROW(){
  Serial.println("enterROW Start");
  int buttoni;
  
  bt1 = digitalRead(buttonPin1);

  while(1){
  buttonState1=digitalRead(buttonPin1);

  if(bt1 !=0&&  buttonState1==0){
    Serial.println("Button1 Pressed");
    buttoni=1;
    return buttoni;
   }

  bt1=buttonState1;
  }
}

void WinCheckField_Data(){
  Serial.println("WinCheckField_Data Start");
  int row = blockBlink();
  Serial.print("WinCheck row : ");
  Serial.println(row);
  if(flag == 0) flag = 1; else flag = 0;
  int col = empty_check(row);
  Serial.print("WinCheck col : ");
  Serial.println(col);
  Serial.print("Before WinCheckField[row][col] : ");
  Serial.println(WinCheckField[row][col]);
  if(col != 0x1F && WinCheckField[row][col] == 8) {
    WinCheckField[row][col] = flag;
    Serial.print("After WinCheckField[row][col] : ");
    Serial.println(WinCheckField[row][col]);
    if(WinCheckField[row][col] == 1)
      showBlockcolor1(row, col+1);
    else
      showBlockcolor2(row, col+1);
    /* int led = calcLED(row, col+1);
    Serial.print("WinCheckField_Data led : ");
    Serial.println(led); */
    col = e[row]++;
    return col;
  } else {
    //WinCheckField_Data();
  }
}

int empty_check(int i) {
  return e[i];
}

int blockBlink(){
  Serial.println("blockBlink Start");
  int i = enterROW();
  int j = 21;

  while(j>=1){
    showBlockcolor1(i, j);
    delay(100);
    j = j-4;
    clearPIXELS();
  }
  Serial.println("blockBlink END");
  return i;
}

/* void LEDon_byData(){
  int led = WinCheckField_Data();
  Serial.print("led = ");
  Serial.println(led);
  
  showBlock(led);
  Serial.println("LEDon_byData() ON");
} */

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);
  
  pinMode(buttonPin1, INPUT);

  pixelarraySetup();
}

void loop() {
  //blockBlink();
  //clearPIXELS();
  WinCheckField_Data();
}
