void pixelarrayInit(){                    // Wincheck값 초기화
  for(int i=0; i<ROW; i++) {
      for(int j=0; j<COL; j++) {
            WinCheckField[i][j] = 8;  
      }
      e[i] = 0x00;
  }
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
    if(WinCheckField[row][col] == 1) showBlockcolor(4*row+1, 4*col+1, colorPlayer1);
    else showBlockcolor(4*row+1, 4*col+1, colorPlayer2);
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
