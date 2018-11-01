uint32_t colorPlayer1;
uint32_t colorPlayer2;

int calcLED(int row, int col){
  int odd = row%2;
  int led = 0;

  if(odd){
   if(col >= 1 && col <= 8){
      led = 8*row - col;
      if(flag == 0) return led;
      else return led+800;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row - col + 264;
      if(flag == 0) return led;
      else return led+800;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row - col + 528;
      if(flag == 0) return led;
      else return led+800;
    }
  }

  else{
    if(col >= 1 && col <= 8){
      led = 8*row + col - 9;
      if(flag == 0) return led;
      else return led+800;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row + col - 9 + 248;
      if(flag == 0) return led;
      else return led+800;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row + col - 9 + 496;
      if(flag == 0) return led;
      else return led+800;
    }
  }
}

int enterRow(){
  Serial.println("enterRow Start");
  
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
    if(flag == 0) return 0;
    else return 6;
   }
   else if(bt2 !=0 && buttonState2==0){
    Serial.println("Button2 Pressed");
    if(flag == 0) return 1;
    else return 5;
   }
   else if(bt3 !=0 && buttonState3==0){
    Serial.println("Button3 Pressed");
    if(flag == 0) return 2;
    else return 4;
   }
   else if(bt4 !=0 && buttonState4==0){
    Serial.println("Button4 Pressed");
    return 3;
   }
   else if(bt5 !=0 && buttonState5==0){
    Serial.println("Button5 Pressed");
    if(flag == 0) return 4;
    else return 2;
   }
   else if(bt6 !=0 && buttonState6==0){
    Serial.println("Button6 Pressed");
    if(flag == 0) return 5;
    else return 1;
   }
   else if(bt7 !=0 && buttonState7==0){
    Serial.println("Button7 Pressed");
    if(flag == 0) return 6;
    else return 0;
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
    Serial.println("All Player Ready");
    gamestatus = 2;
    clearPIXELS();
  }
  else enterPlayer();
}

int empty_check(int i) {
  return e[i];
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
    showBlockcolor(4*i+1, top, colorPlayer1);
    delay(100);
    if(top > 4*j+1) showBlockcolor(4*i+1, top, 0);
    top = top - 4;
  }
  }
  else{
    while(top >= 4*j+1){
    showBlockcolor(4*i+1, top, colorPlayer2);
    delay(100);
    if(top > 4*j+1) showBlockcolor(4*i+1, top, 0);
    top = top - 4;
  }
  }
  Serial.println("blockBlink END");
}

void enterAnyKey(){
  Serial.println("enterAnyKey Start");
  Serial.print("mouseIsActive : ");
  Serial.println(mouseIsActive);
  int switchState = digitalRead (buttonPin1) | digitalRead (buttonPin2) | digitalRead (buttonPin3) 
                  | digitalRead (buttonPin4) | digitalRead (buttonPin5) | digitalRead (buttonPin6)| digitalRead (buttonPin7); // Press Any Key
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      Serial.println("Button Pressed");
      mouseIsActive = !mouseIsActive;
      Serial.print("mouseIsActive : ");
      Serial.println(mouseIsActive);
      MsTimer2::stop();
    }
  }
  lastSwitchState = switchState;
}

void StartingScreen(){                  // 오프닝 화면
  MsTimer2::start();
  pixels.setBrightness(20);
  display_LEDGo();
  if(mouseIsActive == 0) dimmingLED();
  else gamestatus = 1;
  pixels.setBrightness(20);
  display_PressAnyKey();
  if(mouseIsActive == 0) dimmingLED();
  else gamestatus = 1;
}

void selectColorPlayer1(){
  Serial.println("selectColorPlayer1 Start");

  MsTimer2::start();
  
  while(mouseIsActive){
    Serial.println("Selecting Color ...");
    int colorDial = analogRead(colorPotPin);
    colorDial = map(colorDial, 0, 1023, 0, 49);
       
    if(colorDial >= 0 && colorDial < 7){
      colorPlayer1 = C0;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 7 && colorDial < 14){
      colorPlayer1 = C1;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 14 && colorDial < 21){
      colorPlayer1 = C2;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 21 && colorDial < 28){
      colorPlayer1 = C3;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 28 && colorDial < 35){
      colorPlayer1 = C4;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 35 && colorDial < 42){
      colorPlayer1 = C5;
      showBlockcolor(15, 4, colorPlayer1);
    }
    else if(colorDial >= 42 && colorDial <= 49){
      colorPlayer1 = C6;
      showBlockcolor(15, 4, colorPlayer1);
    }
    delay(100);
  }
  gamestatus = 3;
  Serial.println("selectColor End");
  MsTimer2::stop();
  clearPIXELS();
}

void selectColorPlayer2(){
  Serial.println("selectColorPlayer2 Start");

  MsTimer2::start();
  
  while(!mouseIsActive){
    Serial.println("Selecting Color ...");
    int colorDial = analogRead(colorPotPin);
    colorDial = map(colorDial, 0, 1023, 0, 49);
       
    if(colorDial >= 0 && colorDial < 7){
      colorPlayer2 = C0;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 7 && colorDial < 14){
      colorPlayer2 = C1;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 14 && colorDial < 21){
      colorPlayer2 = C2;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 21 && colorDial < 28){
      colorPlayer2 = C3;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 28 && colorDial < 35){
      colorPlayer2 = C4;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 35 && colorDial < 42){
      colorPlayer2 = C5;
      showBlockcolor(15, 4, colorPlayer2);
    }
    else if(colorDial >= 42 && colorDial <= 49){
      colorPlayer2 = C6;
      showBlockcolor(15, 4, colorPlayer2);
    }
    delay(100);
  }
  if(colorPlayer1 == colorPlayer2){
    Serial.println("Same Color Selected. Select Again");
    gamestatus = 3;
    mouseIsActive = !mouseIsActive;
  }
  else gamestatus = 4;
  Serial.println("selectColor End");
  MsTimer2::stop();
  clearPIXELS();
}
