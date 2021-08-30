#include <Servo.h>
#define TRIG 8
#define ECHO 9

Servo servo;
int servoDirection = 1, rad = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(10);
}

void loop() {
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);

  long distance = pulseIn(ECHO, HIGH, 5800)/58;

  Serial.print("r");
  Serial.print(rad);
  Serial.print("d");
  Serial.print(distance);

  rad += servoDirection;
  if(rad > 180){
    rad = 179;
    servoDirection = -1;
  }else if(rad < 0){
    rad = 1;
    servoDirection = 1;
  }
  servo.write(rad);
  delay(15); // 각도가 바뀌는걸 기다려주는 시간
  }
}
