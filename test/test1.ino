#include <Servo.h>

/*[모터드라이버]
 오른쪽 모터 
  A_1A D6
  A_1B D6
 왼쪽 모터
  B_1A D3
  B_1B D5
*/
int A_1A = 6;
int A_1B = 11;
int B_1A = 3;
int B_1B = 5;
//아두이노 핀 번호

/* [초음파센서]
  TRIG(송신부) D8
  ECHO(수신부) D9
*/
int trigPin = 8;
int echoPin = 9;

/* [서보모터]
  서보모터 OUT(신호선) D10
*/
int servoPin = 10;

Servo servo;

/* [모터 속도](0~255) */
int motorASpeed = 150;
int motorBSpeed = 150;

void setup() {
  Serial.begin(9600); // 초당 9600비트의 속도로 통신
  // 핀을 입력으로 쓸지 출력으로 쓸지 결정(OUTPUT = 출력, INPUT = 입력)
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  
  // 주어진 핀번호에 대해 값을 기록하는 기능(HIGH = 해당 핀에 5V 전류가 흐르게, LOW = 해당  핀에 5V 전류가 흐르는 것을 차단)
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);

  // 초음파센서를 초기화
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // 서보모터 연결
  servo.attach(servoPin);

  // 초기에 서보를 정면으로 바라보도록 정렬
  servo.write(90);
  delay(1000);
}

void loop() {
  int cm = getStableDistanceCM();
  long leftDistance = 0;
  long rightDistance = 0;

  // 25cm 이내에 벽이 존재
  if(cm < 25) {
    stop();
    delay(500);
    // 왼쪽 거리 측정
    servo.write(150);
    delay(500);
    leftDistance = getStableDistanceCM();
    delay(500);
    // 오른쪽 거리 측정
    servo.write(30);
    delay(500);
    rightDistance = getStableDistanceCM();
    delay(500);
    // 서보모터 중앙정렬
    servo.write(90);
    delay(1000);
    // 후진
    back();
    delay(300);
    // 거리가 더 먼쪼긍로 회전
    if(leftDistance > rightDistance) left();
    else right();

    delay(500);
  }
  else{
    forward(); // 벽이 없으면 계속 전진한다는 거
  }
}

/*
 전방 거리측정(CM)
 초음파센서를 이용해서 벽까지 거리(mm)를 구함.
 */
float getDistanceCM() {
  digitalWrite(echoPin, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 거리값
  // pulseIn(echoPin, HIGH) -> HIGH에서 LOW로 바뀌는데 걸리는 시간
  // 초음파의 속도 340m/s
  // 초음파 센서를 이용한 거리 계산식 이용.
  float distance = pulseIn(echoPin, HIGH) / 29.0 / 2.0;

  return distance;
}


/*
 전방에 신뢰할 수 있는 거리측정(CM)
 센서에 오차가 있으므로 평균값 구해야 함.
 */
float getStableDistanceCM() {
  int CmSum = 0;
  for(int i = 0; i < 10; i++) {
    CmSum += getDistanceCM();
  }

  return CmSum / 10;
}

/* [모터를 이용한 주행] */
// analogWrite(핀 번호, 전압), 0V~5V인 전압 부분은 0 ~ 255로 설정 가능
// digitalWrite에서 세기를 조절할려면 analogWrite
void forward() {
  // 모터 A 정회전
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0); // A_1A와 A_1B를 조절하면서 정회전, 역회전 조절가능
  // 모터 B 정회전
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

void back() {
  // 모터 A 역회전
  analogWrite(A_1A, 0);
  analogWrite(A_1B, motorASpeed);
  // 모터 B 역회전
  analogWrite(B_1A, 0);
  analogWrite(B_1B, motorBSpeed);
}

void left() {
  // 모터 A 정회전
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0);
  // 모터 B 정지
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}

void right() {
  // 모터 A 정지
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  // 모터 B 정회전
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

void stop() {
  // 모터 A 정지
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  // 모터 B 정지
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}
