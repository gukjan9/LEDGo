void display_PixelColor(int led, uint32_t color) {
  if(displaymode == 0){
    pixels.setPixelColor(led, color);
    pixels.setPixelColor(led+768, color);
  }
  else if(displaymode == 1){
    pixels.setPixelColor(led, color);
  }
  else if(displaymode == 2){  // blockBLink때
    pixels.setPixelColor(led, color);
    pixels.setPixelColor(display_2Matrix(calcReverse(led)), color);
    }
  else if(displaymode == 3){
    pixels.setPixelColor(led+768, color);
  }
  pixels.show();
}

void clearPIXELS(){
  Serial.println("Clearing Pixels...");
  
  for (int i=0; i<PIXELS_COUNT; i++){
    pixels.setPixelColor(i, 0);
  }
}

int notPrevRandomColor(int previous){         // Not same previous random color 
  int min = 0;
  int max = 12;
  int color = random(0, 12);
  
  if(previous == color){
    Serial.println("Same Color Selected");
    notPrevRandomColor(previous);
  }
  else return color;
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

int Quotient(int x, int y){               // 몫 함수
  int q = x / y;
  
  return q;
}

int Remainder(int x, int y){              // 나머지 함수
  int r = x % y;

  return r;
}

void display_4bit(int data, int textRow, int textCol, uint32_t color){              // ■■■■ 구현
  int division = 16;
  
  while(division != 0){
    int valBit = data & division;

    if(valBit == 0) valBit = 0;
    else valBit = 1;
 
    if(division == 0x08) display_PixelColor(calcLED((4+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x04) display_PixelColor(calcLED((3+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x02) display_PixelColor(calcLED((2+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x01) display_PixelColor(calcLED((1+textRow)*valBit, textCol*valBit), color);
    division = division / 2;
  }
}

void display_5bit(int data, int textRow, int textCol, uint32_t color){              // ■■■■■ 구현
  int division = 16;
  
  while(division != 0){
    int valBit = data & division;

    if(valBit == 0) valBit = 0;
    else valBit = 1;
 
    if(division == 0x10) display_PixelColor(calcLED((5+textRow)*valBit, textCol*valBit), color);             // (6*textRow) -> 1줄에 5글자일때 일정간격 띄운것
    else if(division == 0x08) display_PixelColor(calcLED((4+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x04) display_PixelColor(calcLED((3+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x02) display_PixelColor(calcLED((2+textRow)*valBit, textCol*valBit), color);
    else if(division == 0x01) display_PixelColor(calcLED((1+textRow)*valBit, textCol*valBit), color);
    division = division / 2;
  }
}

void display_4PixelHex(int hex, int textRow, int textCol, uint32_t color){             // hex값에 따라 ■■■■ 구현
  int quotient = hex;
  int data = 0x00;
  
  while(quotient != 0){
    int temp_remainder = Remainder(quotient, 2);
    data = temp_remainder | data;
    data = data << 1;
    quotient = Quotient(quotient, 2);
  }
  display_4bit(hex, textRow, textCol, color);
}

void display_5PixelHex(int hex, int textRow, int textCol, uint32_t color){             // hex값에 따라 ■■■■■ 구현
  int quotient = hex;
  int data = 0x00;
  
  while(quotient != 1){
    int temp_remainder = Remainder(quotient, 2);
    data = temp_remainder | data;
    data = data << 1;
    quotient = Quotient(quotient, 2);
  }
  display_5bit(hex, textRow, textCol, color);
}

void display_4Alphabet(char alphabet, int textRow, int textCol, uint32_t color){           // 4X6 Alphabet 정의  
  int Alphabet[44][6] = 
  {{0x06, 0X09, 0X09, 0X09, 0X09, 0X06}, // 0
  {0X0f, 0X04, 0X04, 0X05, 0X06, 0X04}, // 1
  {0X0F, 0X02, 0X04, 0X08, 0X09, 0X06}, // 2
  {0X07, 0X08, 0X08, 0X0F, 0X08, 0X07}, // 3
  {0X08, 0X08, 0X0F, 0X09, 0X09, 0X09}, // 4
  {0X0F, 0X08, 0X08, 0X09, 0X01, 0X0F}, // 5
  {0X0F, 0X09, 0X09, 0X0F, 0X01, 0X0F}, // 6
  {0X08, 0X08, 0X08, 0X09, 0X09, 0X0F}, // 7
  {0X0F, 0X09, 0X09, 0X0F, 0X09, 0X0F}, // 8
  {0X0F, 0X08, 0X08, 0X0F, 0X09, 0X0F}, // 9
  {},{},{},{},{},{},{},
  {0X09, 0X09, 0X0F, 0X09, 0X09, 0X06}, // A
  {0X07, 0X09, 0X09, 0X0F, 0X09, 0X07}, // B
  {0X0E, 0X01, 0X01, 0X01, 0X01, 0X0E}, // C
  {0X07, 0X09, 0X09, 0X09, 0X09, 0X07}, // D
  {0X0F, 0X01, 0X01, 0X0F, 0X01, 0X0F}, // E
  {0X01, 0X01, 0X01, 0X0F, 0X01, 0X0F}, // F
  {0X0E, 0X09, 0X0D, 0X01, 0X01, 0X0E}, // G
  {0X09, 0X09, 0X09, 0X0F, 0X09, 0X09}, // H
  {0X07, 0X02, 0X02, 0X02, 0X02, 0X07}, // I
  {0X02, 0X05, 0X04, 0X04, 0X04, 0X0F}, // J
  {0X09, 0X09, 0X05, 0X03, 0X05, 0X09}, // K
  {0X0F, 0X01, 0X01, 0X01, 0X01, 0X01}, // L
  {0X09, 0X09, 0X09, 0X09, 0X0F, 0X09}, // M
  {0X09, 0X09, 0X0D, 0X0B, 0X09, 0X09}, // N
  {0X06, 0X09, 0X09, 0X09, 0X09, 0X06}, // O
  {0X01, 0X01, 0X07, 0X09, 0X09, 0X07}, // P
  {0X0A, 0X05, 0X09, 0X09, 0X09, 0X06}, // Q
  {0X09, 0X05, 0X07, 0X09, 0X09, 0X07}, // R
  {0X06, 0X09, 0X04, 0X02, 0X09, 0X06}, // S
  {0X02, 0X02, 0X02, 0X02, 0X02, 0X07}, // T
  {0X0F, 0X09, 0X09, 0X09, 0X09, 0X09}, // U 
  {0X06, 0X0F, 0X09, 0X09, 0X09, 0X09}, // V
  {0X09, 0X0F, 0X09, 0X09, 0X09, 0X09}, // W
  {0X09, 0X09, 0X06, 0X06, 0X09, 0X09}, // X
  {0X06, 0X06, 0X06, 0X09, 0X09, 0X09}, // Y
  {0X0F, 0X01, 0X02, 0X04, 0X08, 0X0F}}; // Z
                   
  int ascii = alphabet;

  display_4PixelHex(Alphabet[ascii - 48][0], textRow, 1+(textCol*8), color);
  display_4PixelHex(Alphabet[ascii - 48][1], textRow, 2+(textCol*8), color);
  display_4PixelHex(Alphabet[ascii - 48][2], textRow, 3+(textCol*8), color);
  display_4PixelHex(Alphabet[ascii - 48][3], textRow, 4+(textCol*8), color);
  display_4PixelHex(Alphabet[ascii - 48][4], textRow, 5+(textCol*8), color);
  display_4PixelHex(Alphabet[ascii - 48][5], textRow, 6+(textCol*8), color);
}

void display_4Number_1P(int num, int textRow, int textCol, uint32_t color){  
  int Number[10][6] = 
  {{0x06, 0X09, 0X09, 0X09, 0X09, 0X06}, // 0
  {0X0f, 0X04, 0X04, 0X05, 0X06, 0X04}, // 1
  {0X0F, 0X02, 0X04, 0X08, 0X09, 0X06}, // 2
  {0X07, 0X08, 0X08, 0X0F, 0X08, 0X07}, // 3
  {0X08, 0X08, 0X0F, 0X09, 0X09, 0X09}, // 4
  {0X0F, 0X08, 0X08, 0X09, 0X01, 0X0F}, // 5
  {0X0F, 0X09, 0X09, 0X0F, 0X01, 0X0F}, // 6
  {0X08, 0X08, 0X08, 0X09, 0X09, 0X0F}, // 7
  {0X0F, 0X09, 0X09, 0X0F, 0X09, 0X0F}, // 8
  {0X0F, 0X08, 0X08, 0X0F, 0X09, 0X0F}}; // 9

  display_4PixelHex(Number[num][0], textRow, 1+textCol, color);
  display_4PixelHex(Number[num][1], textRow, 2+textCol, color);
  display_4PixelHex(Number[num][2], textRow, 3+textCol, color);
  display_4PixelHex(Number[num][3], textRow, 4+textCol, color);
  display_4PixelHex(Number[num][4], textRow, 5+textCol, color);
  display_4PixelHex(Number[num][5], textRow, 6+textCol, color);
}

void display_4Number_2P(int num, int textRow, int textCol, uint32_t color){  
  int Number[10][6] = 
  {{0x06, 0X09, 0X09, 0X09, 0X09, 0X06}, // 0
   {0X04, 0X06, 0X05, 0X04, 0X04, 0X0F}, // 1
   {0X06, 0X09, 0X08, 0X04, 0X02, 0X0F}, // 2
   {0X07, 0X08, 0X0F, 0X08, 0X08, 0X07}, // 3
   {0X09, 0X09, 0X09, 0X0F, 0X08, 0X08}, // 4
   {0X0F, 0X01, 0X0F, 0X08, 0X08, 0X0F}, // 5
   {0X0F, 0X01, 0X0F, 0X09, 0X09, 0X0F}, // 6
   {0X0F, 0X09, 0X09, 0X08, 0X08, 0X08}, // 7
   {0X0F, 0X09, 0X0F, 0X09, 0X09, 0X0F}, // 8
   {0X0F, 0X09, 0X0F, 0X08, 0X08, 0X0F}}; // 9

  display_4PixelHex(Number[num][0], textRow, 1+textCol, color);
  display_4PixelHex(Number[num][1], textRow, 2+textCol, color);
  display_4PixelHex(Number[num][2], textRow, 3+textCol, color);
  display_4PixelHex(Number[num][3], textRow, 4+textCol, color);
  display_4PixelHex(Number[num][4], textRow, 5+textCol, color);
  display_4PixelHex(Number[num][5], textRow, 6+textCol, color);
}

void display_5Alphabet(char alphabet, int textRow, int textCol, uint32_t color){           // 5X7 Alphabet 정의  
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

    display_5PixelHex(Alphabet[ascii - 48][0], textRow, 1+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][1], textRow, 2+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][2], textRow, 3+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][3], textRow, 4+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][4], textRow, 5+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][5], textRow, 6+(textCol*8), color);
    display_5PixelHex(Alphabet[ascii - 48][6], textRow, 7+(textCol*8), color);
}

void display_Arrow(int textRow, int textCol, uint32_t color){
  int arrow[1][7] = {0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x0E, 0x04};

  display_5PixelHex(arrow[0][0], textRow, 1+(textCol*8), color);
  display_5PixelHex(arrow[0][1], textRow, 2+(textCol*8), color);
  display_5PixelHex(arrow[0][2], textRow, 3+(textCol*8), color);
  display_5PixelHex(arrow[0][3], textRow, 4+(textCol*8), color);
  display_5PixelHex(arrow[0][4], textRow, 5+(textCol*8), color);
  display_5PixelHex(arrow[0][5], textRow, 6+(textCol*8), color);
  display_5PixelHex(arrow[0][6], textRow, 7+(textCol*8), color);
}

void display_Firework(int i, uint32_t color){
  int j;
  for(j=1; j<=12; j++){                             // l자 Firework
    display_PixelColor(calcLED(i+3,j), C0);
    delay(20);
    display_PixelColor(calcLED(i+3,j), 0);
  }
  display_PixelColor(calcLED(i+3,12), color);      // Small Firework
  display_PixelColor(calcLED(i+2,13), color);
  display_PixelColor(calcLED(i+4,13), color);
  display_PixelColor(calcLED(i+2,11), color);
  display_PixelColor(calcLED(i+4,11), color);
  delay(30);
  display_PixelColor(calcLED(i+3,12), 0);
  display_PixelColor(calcLED(i+2,13), 0);
  display_PixelColor(calcLED(i+4,13), 0);
  display_PixelColor(calcLED(i+2,11), 0);
  display_PixelColor(calcLED(i+4,11), 0);
  delay(30);
  display_PixelColor(calcLED(i+3,13), color);      // Big Firework
  display_PixelColor(calcLED(i+3,14), color);
  display_PixelColor(calcLED(i+4,12), color);
  display_PixelColor(calcLED(i+5,12), color);
  display_PixelColor(calcLED(i+3,10), color);
  display_PixelColor(calcLED(i+3,11), color);
  display_PixelColor(calcLED(i+1,12), color);
  display_PixelColor(calcLED(i+2,12), color);
  delay(30);
  display_PixelColor(calcLED(i+3,13), 0);
  display_PixelColor(calcLED(i+3,14), 0);
  display_PixelColor(calcLED(i+4,12), 0);
  display_PixelColor(calcLED(i+5,12), 0);
  display_PixelColor(calcLED(i+3,10), 0);
  display_PixelColor(calcLED(i+3,11), 0);
  display_PixelColor(calcLED(i+1,12), 0);
  display_PixelColor(calcLED(i+2,12), 0);
  delay(30);
}

void display_LEDGo(){
  Serial.println("Welcome to LEDGo!");
  if(!mouseIsActive) display_Firework(2, C1);
  if(!mouseIsActive) display_5Alphabet('L', 2, 1, C1);
  if(!mouseIsActive) display_Firework(8, C7);
  if(!mouseIsActive) display_5Alphabet('E', 8, 1, C7);
  if(!mouseIsActive) display_Firework(14, C2);
  if(!mouseIsActive) display_5Alphabet('D', 14, 1, C2);
  if(!mouseIsActive) display_Firework(20, C8);
  if(!mouseIsActive) display_5Alphabet('G', 20, 1, C8);
  if(!mouseIsActive) display_Firework(26, C9);
  if(!mouseIsActive) display_5Alphabet('O', 26, 1, C9);
}

void display_PressAnyKey(){
  Serial.println("Press Any Key to Start");
  if(!mouseIsActive) display_5Alphabet('P', 2, 2, C1);
  if(!mouseIsActive) display_5Alphabet('R', 8, 2, C7);
  if(!mouseIsActive) display_5Alphabet('E', 14, 2, C2);
  if(!mouseIsActive) display_5Alphabet('S', 20, 2, C8);
  if(!mouseIsActive) display_5Alphabet('S', 26, 2, C3);

  if(!mouseIsActive) display_5Alphabet('A', 8, 1, C4);
  if(!mouseIsActive) display_5Alphabet('N', 14, 1, C9);
  if(!mouseIsActive) display_5Alphabet('Y', 20, 1, C5);

  if(!mouseIsActive) display_5Alphabet('K', 8, 0, C0);
  if(!mouseIsActive) display_5Alphabet('E', 14, 0, C0);
  if(!mouseIsActive) display_5Alphabet('Y', 20, 0, C0);
}

void dimmingLED(){
  int lux;
  Serial.println("Dimming Brightness");
  for(lux = 20; lux >= 0; lux--){
    Serial.print("Lux : ");
    Serial.println(lux);
    pixels.setBrightness(lux);
    pixels.show();
    delay(70);
  }
}

void display_Player(){
  pixels.setBrightness(20);
  pixels.show();
  Serial.println("Waiting for Player1 and Player2");
  
  int ranColor1 = random(0, 12);
  Serial.print("Player Color : ");
  Serial.println(ranColor1);
  int ranColor2 = notPrevRandomColor(ranColor1);
  Serial.print("Player Number Color : ");
  Serial.println(ranColor2);

  display_4Alphabet('P', 1, 2, colors[ranColor1]);
  display_4Alphabet('L', 6, 2, colors[ranColor1]);
  display_4Alphabet('A', 11, 2, colors[ranColor1]);
  display_4Alphabet('Y', 16, 2, colors[ranColor1]);
  display_4Alphabet('E', 21, 2, colors[ranColor1]);
  display_4Alphabet('R', 26, 2, colors[ranColor1]);

  displaymode = 1;
  
  display_5Alphabet('1', 12, 1, colors[ranColor2]);

  displaymode = 3;
  
  display_5Alphabet('2', 12, 1, colors[ranColor2]);
}

void displayReady(int player){
  Serial.print("Player ");
  Serial.print(player);
  Serial.println(" is Ready !");
  int col;
  
  mp3Sound(2);
  
  display_5Alphabet('R', 0, 0, C1);
  display_5Alphabet('E', 6, 0, C7);
  display_5Alphabet('A', 12, 0, C2);
  display_5Alphabet('D', 18, 0, C8);
  display_5Alphabet('Y', 24, 0, C9);
}

void displaySelectColor(){
  Serial.println("Select Player1 and Player2 Color");

  int ranColor1 = random(0, 12);
  Serial.print("ranColor1 : ");
  Serial.println(ranColor1);
  int ranColor2 = notPrevRandomColor(ranColor1);
  Serial.print("ranColor2 : ");
  Serial.println(ranColor2);

  display_4Alphabet('S', 1, 2, colors[ranColor1]);
  display_4Alphabet('E', 6, 2, colors[ranColor1]);
  display_4Alphabet('L', 11, 2, colors[ranColor1]);
  display_4Alphabet('E', 16, 2, colors[ranColor1]);
  display_4Alphabet('C', 21, 2, colors[ranColor1]);
  display_4Alphabet('T', 26, 2, colors[ranColor1]);

  display_5Alphabet('C', 0, 1, colors[ranColor2]);
  display_5Alphabet('O', 6, 1, colors[ranColor2]);
  display_5Alphabet('L', 12, 1, colors[ranColor2]);
  display_5Alphabet('O', 18, 1, colors[ranColor2]);
  display_5Alphabet('R', 24, 1, colors[ranColor2]);
}

void display_Score(){
  displaymode = 2;
  display_4Number_1P(scorePlayer1, 28, 1, colorPlayer1);
  display_4Number_2P(scorePlayer2, 28, 17, colorPlayer2);
}

void blinkWinBlock(int A, int B, int C, int D, int a, int b, int c, int d, uint32_t color){
  Serial.println("blinkWinBlock Start");
  MsTimer2::start();
  
  while(mouseIsActive){
    Serial.println("Blinking Win Block...");
    mp3Sound(7);
    showBlockcolor(A, a, 0);
    showBlockcolor(B, b, 0);
    showBlockcolor(C, c, 0);
    showBlockcolor(D, d, 0);
    delay(500);
    mp3Sound(7);
    showBlockcolor(A, a, color);
    showBlockcolor(B, b, color);
    showBlockcolor(C, c, color);
    showBlockcolor(D, d, color);
  }
  mp3Sound(8);
  Serial.println("blinkWinBlock End");
}

void display_WinLose(){
  clearPIXELS();
  if(flag == 1){
    Serial.println("Player 1 WIN !");
    scorePlayer1++;
    winnerColor = colorPlayer1;
    displaymode = 3;
    display_5Alphabet('L', 5, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('W', 8, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('O', 11, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('I', 14, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('S', 17, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('N', 20, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('E', 23, 1, colorPlayer2);
    mp3Sound(9);
  }
  else{
    Serial.println("Player 2 WIN !");
    scorePlayer2++;
    winnerColor = colorPlayer2;
    displaymode = 1;
    display_5Alphabet('L', 5, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('W', 8, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('O', 11, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('I', 14, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('S', 17, 1, colorPlayer1);
    displaymode = 3;
    display_5Alphabet('N', 20, 1, colorPlayer2);
    displaymode = 1;
    display_5Alphabet('E', 23, 1, colorPlayer1);
    mp3Sound(9);
  }
  delay(7000);
  clearPIXELS();
}

void display_Continue(uint32_t color){
  display_4Alphabet('C', 1, 1, color);
  display_4Alphabet('O', 6, 1, color);
  display_4Alphabet('N', 11, 1, color);
  display_4Alphabet('T', 16, 1, color);
  display_4Alphabet('I', 1, 0, color);
  display_4Alphabet('N', 6, 0, color);
  display_4Alphabet('U', 11, 0, color);
  display_4Alphabet('E', 16, 0, color);
}

void display_Quit(uint32_t color){
  display_4Alphabet('Q', 21, 1, color);
  display_4Alphabet('U', 26, 1, color);
  display_4Alphabet('I', 21, 0, color);
  display_4Alphabet('T', 26, 0, color);
}
