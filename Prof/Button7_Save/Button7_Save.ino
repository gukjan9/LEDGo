
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
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    Serial.println("Button1 Pressed");
  } else if (buttonState2 == HIGH) {
    Serial.println("Button2 Pressed");
  } else if (buttonState3 == HIGH) {
    Serial.println("Button3 Pressed");
  } else if (buttonState4 == HIGH) {
    Serial.println("Button4 Pressed");
  } else if (buttonState5 == HIGH) {
    Serial.println("Button5 Pressed");
  } else if (buttonState6 == HIGH) {
    Serial.println("Button6 Pressed");
  } else if (buttonState7 == HIGH) {
    Serial.println("Button7 Pressed");
  }
}
