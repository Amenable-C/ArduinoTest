#define ENCODER 2

volatile int encoder = 0; // 엔코더를 지나간 디스크의 구멍 수를 저장하는 변수 // 값이 계속 바뀌기 때문에, 그 때 생기는 문제를 방지하기 위해서 volatile 사용

void ISR_encoder() {
  encoder++;  // 구멍 수 +1
}

void setup() {
  Serial.begin(57600);  // 57600bps 속도로 시리얼 통신 시작
  pinMode(ENCODER, INPUT_PULLUP); // 엔코더를 내부 풀업 저항을 사용하는 입력으로 설정
  attachInterrupt(digitalPinToInterrupt(ENCODER), ISR_encoder, FALLING); 
  // 인터럽트 : 현재 프로그램이 수행 도중에 어떤 상황이 발생했을 때 수행중인 프로그램을 일시 중단하고 특정 동작을 수행하게 하는 방식
  // FALLING : High -> Low 상태
  // FALLING이 되면 ISR_encoder 함수 호출
  // attachInterrupt(인터럽트넘버, 호출함수, 상태조건);
  // 해당 체크핀에 대해 특정 상태조건이 되면 인터럽트가 발동되고 호출함수를 호출하게 된다.
  // digitalPinToInterrupt(사용핀)을 이용해서 직접적으로 해당핀을 지칭
}

unsigned long timePrev = 0; // 이전 시간을 저장하는 변수(0으로 초기화)
unsigned long timeCurr = 0; // 현재 시간을 저장하는 변수(0으로 초기화)

void loop() {
  timeCurr = millis();  // ms단위로 현재 시간 받아오기
  if(timeCurr - timePrev > 1000){ // 1초 마다 출력(1000ms = 1s)
    timePrev = timeCurr;  // 이전 시간을 현재 시간으로 업데이트
    noInterrupts(); // 인터럽트를 비활성화
    Serial.print(timeCurr/1000);  // 현재 시간을 초 단위로 출력
    Serial.print(": ");
    Serial.printIn(encoder);  // 엔코더를 지나간 디스크의 구멍 수 출력
    interrupts(); // 인터럽트를 다시 활성화
    }
}
