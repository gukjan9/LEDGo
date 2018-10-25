uint32_t C0 = 0xFFFFFF; //White
uint32_t C1 = 0xFF0000; //Red
uint32_t C2 = 0xFFFF00; //Yellow
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x00FFFF; //Cyan
uint32_t C5 = 0x0000FF; //Blue
uint32_t C6 = 0xFF00FF; //Magenta


void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      //pixels.setPixelColor(led+768, color);
      pixels.show();
}

void clearPIXELS(){
  Serial.println("Clearing Pixels...");
  
  for (int i=0; i<PIXELS_COUNT; i++){
    pixels.setPixelColor(i, 0);
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

uint32_t MyColors[7] = {C0, C1, C2, C3, C4, C5, C6}; //put the colors in an array

uint32_t color2 = MyColors[1];
uint32_t color1 = MyColors[2];
uint32_t color3 = MyColors[6];


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

void display_Firework(int i){
  int j;
  for(j=1; j<=12; j++){                             // l자 Firework
    display_PixelColor(calcLED(i+3,j), color3);
    delay(70);
    display_PixelColor(calcLED(i+3,j), 0);
  }
  display_PixelColor(calcLED(i+3,12), color3);      // Small Firework
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
  display_PixelColor(calcLED(i+3,13), color3);      // Big Firework
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
  pixels.setBrightness(20);
  pixels.show();
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

void displaySelectColor(int player){
  Serial.print("Select Player");
  Serial.print(player);
  Serial.println(" Color");

  display_Alphabet('S', 0, 2);
  display_Alphabet('E', 6, 2);
  display_Alphabet('L', 12, 2);
  display_Alphabet('E', 18, 2);
  display_Alphabet('C', 24, 2);

  display_Alphabet('C', 0, 1);
  display_Alphabet('O', 6, 1);
  display_Alphabet('L', 12, 1);
  display_Alphabet('O', 18, 1);
  display_Alphabet('R', 24, 1);
}

