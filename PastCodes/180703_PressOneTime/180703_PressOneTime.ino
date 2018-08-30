
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

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  bt1 = digitalRead(buttonPin1);
  bt2 = digitalRead(buttonPin2);
  bt3 = digitalRead(buttonPin3);
  bt4 = digitalRead(buttonPin4);
  bt5 = digitalRead(buttonPin5);
  bt6 = digitalRead(buttonPin6);
  bt7 = digitalRead(buttonPin7);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
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
   }
   if(bt2 !=0&&  buttonState2==0){
    Serial.println("Button2 Pressed");
  }
  if(bt3 !=0&&  buttonState3==0){
    Serial.println("Button3 Pressed");
  }
  if(bt4 !=0&&  buttonState4==0){
    Serial.println("Button4 Pressed");
  }
  if(bt5 !=0&&  buttonState5==0){
    Serial.println("Button5 Pressed");
  }
  if(bt6 !=0&&  buttonState6==0){
    Serial.println("Button6 Pressed");
  }if(bt7 !=0&&  buttonState7==0){
    Serial.println("Button7 Pressed");
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
 
