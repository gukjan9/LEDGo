#ifndef _GAME_H_
#define _GAME_H_

const int buttonPin1 = 23;
const int buttonPin2 = 25;
const int buttonPin3 = 27;
const int buttonPin4 = 29;
const int buttonPin5 = 31;
const int buttonPin6 = 33;
const int buttonPin7 = 35;

const int btnLedPin1 = 39;
const int btnLedPin2 = 41;
const int btnLedPin3 = 43;
const int btnLedPin4 = 45;
const int btnLedPin5 = 47;
const int btnLedPin6 = 49;
const int btnLedPin7 = 51;

int colorPotPin = A0;
int brightPotPin = A1;
int volumePotPin = A2;

int displaymode = 0;
int gamestatus = -1;
int player1 = 0;
int player2 = 0;

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

int ch1 = 48;  
int ch2 = 50;
int ch3 = 52;

int swstate1 = 0;
int swstate2 = 0;
int swstate3 = 0;

int globalRow;

boolean flag=0;
unsigned char e[8];

int e1 = 0;
int e2 = 0;
int e3 = 0;
int e4 = 0;
int e5 = 0;
int e6 = 0;
int e7 = 0;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

uint32_t C0 = 0xFFFFFF; //White
uint32_t C1 = 0xFF0000; //Red
uint32_t C2 = 0xFFFF00; //Yellow
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x00FFFF; //Cyan
uint32_t C5 = 0x0000FF; //Blue
uint32_t C6 = 0xFF00FF; //Magenta

uint32_t C7 = 0xFF8000; //Orange
uint32_t C8 = 0x80FF00; //Yellow Green
uint32_t C9 = 0x0080FF; //Light Blue
uint32_t C10 = 0x7F00FF; //Purple

uint32_t colors[11] = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10}; //put the colors in an array

uint32_t colorPlayer1 = C0;
uint32_t colorPlayer2 = C0;

uint32_t winnerColor;

#endif 
