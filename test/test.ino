#include <Arduino.h>
#include <Servo.h>

#define MOTOR_A_1A 6 // 오른쪽모터 - 아두이노 우노 6번 핀에 연결
#define MOTOR_A_1B 11 // 오른쪽모터 - 아두이노 우노 11번 핀에 연결
#define MOTOR_B_1A 3 // 왼쪽모터 - 아두이노 우노 3번 핀에 연결
#define MOTOR_B_1B 5 // 왼쪽모터 - 아두이노 우노 5번 핀에 연결
#define MOTOR_SPEED 200 //모터의 기준속력입니다(0~255) 기준속력 변경시 제자리 회전 시간 변경이 필요합니다.

unsigned char M_A_spd = 0, M_B_spd = 0;
int speed = 200;

void forward() {
  // 모터 A 정회전
  analogWrite(MOTOR_A_1A, speed);
  analogWrite(MOTOR_A_1B, 0);
  // 모터 B 정회전
  analogWrite(MOTOR_B_1A, speed);
  analogWrite(MOTOR_B_1B, 0);
}
void stop() {
  //모터A 정지
  analogWrite(MOTOR_A_1A, 0);
  analogWrite(MOTOR_A_1B, 0);
  //모터B 정지
  analogWrite(MOTOR_B_1A, 0);
  analogWrite(MOTOR_B_1B, 0);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_A_1A, OUTPUT);
  pinMode(MOTOR_A_1B, OUTPUT);
  pinMode(MOTOR_B_1A, OUTPUT);
  pinMode(MOTOR_B_1B, OUTPUT);
  digitalWrite(MOTOR_A_1A, LOW);
  digitalWrite(MOTOR_A_1B, LOW);
  digitalWrite(MOTOR_B_1A, LOW);
  digitalWrite(MOTOR_B_1B, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // motor_drive();  // 모터를 구동하는 함수
  // delay(2000);
  forward();
  delay(1000);

}
