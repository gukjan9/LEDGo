#ifndef _GAME_H_
#define _GAME_H_

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

uint32_t C0 = 0xFFFFFF; //White
uint32_t C1 = 0xFF0000; //Red
uint32_t C2 = 0xFFFF00; //Yellow
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x00FFFF; //Cyan
uint32_t C5 = 0x0000FF; //Blue
uint32_t C6 = 0xFF00FF; //Magenta

uint32_t MyColors[7] = {C0, C1, C2, C3, C4, C5, C6}; //put the colors in an array

uint32_t color2 = MyColors[1];
uint32_t color1 = MyColors[2];
uint32_t color3 = MyColors[6];

uint32_t colorPlayer1 = color1;
uint32_t colorPlayer2 = color2;

#endif 
