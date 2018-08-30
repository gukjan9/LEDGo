int SW = 8;                         // SW를 8로 설정합니다.
int LED = 9;                        // LED를 9로 설정합니다.

void setup() {
  pinMode(SW, INPUT_PULLUP);        // SW를 풀업인 입력핀으로 설정합니다.
  pinMode(LED, OUTPUT);             // LED를 출력핀으로 설정합니다.
}
void loop() {
  if (digitalRead(SW) == LOW) {     // 만약 SW의 디지털 신호가 LOW라면
    digitalWrite(LED, HIGH);        // LED에 HIGH를 출력합니다.
  } else {                          // SW가 LOW가 아니라면
    digitalWrite(LED, LOW);         // LED에 LOW를 출력합니다.
  }
  delay(100);                       // 0.1초동안 지연합니다.
}

/* 아케이드 버튼
 *  황동색 단자가 왼쪽을 기준으로 위 : GND 아래 : Data
 */


