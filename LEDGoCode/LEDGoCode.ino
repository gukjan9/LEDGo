#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Wire.h>
#include "RTClib.h"
#include "game.h"
#define PIN            3

#define PIXELS_ROWS 32
#define PIXELS_COLUMNS 48
#define PIXELS_COUNT 768 //PIXELS_ROWS * PIXELS_COLUMNS

#define ROW 7
#define COL 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(96, 8, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_SEQUENCE,
  NEO_GRB            + NEO_KHZ800);
  
const uint16_t Mcolors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};
int x = matrix.width();

int WinCheckField[ROW][COL];

boolean flag=0;
unsigned char e[8];

int globalRow;

int gamestatus = 0;
int player1 = 0;
int player2 = 0;

boolean mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

int colorPotPin = A9;

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(10);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);

  pinMode(ch1, INPUT_PULLUP);
  pinMode(ch2, INPUT_PULLUP);
  pinMode(ch3, INPUT_PULLUP);

  rtcFunc();
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (10);

    MsTimer2::set(100, enterAnyKey);

  /* if(gamestatus == 1){
    MsTimer2::set(1000, setTime);
    MsTimer2::start();
  } */

  pixelarrayInit();
}

void loop() {
  if(gamestatus == -1) rtcLed();

  else if(gamestatus == 0){
    StartingScreen();
  }
  else if(gamestatus == 1){
    displayPlayer(1);
    enterPlayer();
  }
  if(gamestatus == 2){
    displaySelectColor(1);
    selectColorPlayer1();
  }
  else if(gamestatus == 3){
    displaySelectColor(2);
    selectColorPlayer2();
  }
  else if(gamestatus == 4){
    blockBlink();
    WinCheckField_Data();
    select_sw();
  }
  else if(gamestatus == 5){
    display_WinLose();
    endGame();
    initializeGame();
  }
}
