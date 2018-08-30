#include <Adafruit_NeoPixel.h>

#define PIN            6
#define NUMPIXELS      56
#define COUNT 8
#define COL 8 //i
#define ROW 6 //j

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

uint8_t data[COL][ROW];
uint8_t counton = 0;
boolean flag=0;
int led;
unsigned char e[8];

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

int bt1=0;
int bt2=0;
int bt3=0;
int bt4=0;
int bt5=0;
int bt6=0;
int bt7=0;

uint32_t color = MyColors[0]; 

void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      pixels.show(); 
      delay(100); 
}

int data_create() {   
  int i = enterCOL();
  int j = empty_check(i);
  if(j <= 5)
  {
  if(flag == 0) flag = 1; else flag = 0;
  }
  if(j != 0x1F && data[i][j] == 8) {
    data[i][j] = flag;
    led = led_count(i,j);
    Serial.print("col = " );
    Serial.println(i);
    Serial.print("row = " );
    Serial.println(j);
    Serial.print("led = " );
    Serial.println(led);
    Serial.println("++++++++++++++++");
    j = e[i]++;
    Serial.print("After press e[i]++ : ");
    Serial.println(j);
    return led;
  } else {
    data_create();
  }  
}

int empty_check(int i) {
  return e[i];
}

int led_count(int i, int j) {
  int location;

  if(i==1) location = 9-i-j-1;
  else if(i==2) location = 5+i+j+1;
  else if(i==3) location = 27-i-j-1;
  else if(i==4) location = 19+i+j+1;
  else if(i==5) location = 45-i-j-1;
  else if(i==6) location = 33+i+j+1;
  else if(i==7) location = 63-i-j-1;

  return location;
}

int enterCOL()
{
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

  if(bt1 !=0&&  buttonState1==0){
    Serial.println("Button1 Pressed");
    buttoni=1;
    return buttoni;
   }
   if(bt2 !=0&&  buttonState2==0){
    Serial.println("Button2 Pressed");
    buttoni=2;
    return buttoni;
  }
  if(bt3 !=0&&  buttonState3==0){
    Serial.println("Button3 Pressed");
    buttoni=3;
    return buttoni;
  }
  if(bt4 !=0&&  buttonState4==0){
    Serial.println("Button4 Pressed");
    buttoni=4;
    return buttoni;
  }
  if(bt5 !=0&&  buttonState5==0){
    Serial.println("Button5 Pressed");
    buttoni=5;
    return buttoni;
  }
  if(bt6 !=0&&  buttonState6==0){
    Serial.println("Button6 Pressed");
    buttoni=6;
    return buttoni;
  }
  if(bt7 !=0&&  buttonState7==0){
    Serial.println("Button7 Pressed");
    buttoni=7;
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
  
  for(int i=0; i<COL; i++) {
      for(int j=0;j<ROW;j++) {
            data[i][j] = 8;  
      }
      e[i] = 0x00;
  }
  Serial.println("###################");
  Serial.println(" Program Start~!!");
  Serial.println("###################");
}

void loop() {  
  led = data_create();
  counton++;
  if(flag == 0) color = MyColors[7]; else color = MyColors[6];
  display_PixelColor(led, color);
  Serial.print("Led = " );
  Serial.println(led);
  Serial.print("Count on = " );
  Serial.println(counton);
  Serial.print("Flag = " );
  Serial.println(flag);
  Serial.println("----------------");
  delay(50);
  if(counton == 42) {
    counton = 0;
    for(int i=0; i<COL; i++) {
      for(int j=0;j<ROW;j++) {
            data[i][j] = 8;  
      }
      e[i] = 0x00;
    }
    delay(2000);
    pixels.clear();
  }
}
