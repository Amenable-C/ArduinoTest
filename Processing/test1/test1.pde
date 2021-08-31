import processing.serial.*;
//import cc.arduino.*;

Serial myPort;
int rad = 0;
float cx, cy; // 원의 센터를 나타냄
ArrayList<Ball> balls = new ArrayList<Ball>(); // <Ball> 이라는 변수 형태

void setup() {
  size(400, 400);
  cx = width / 2; // 센터값 설정
  cy = height * 2/3; // 센터값 설정
  noFill(); // 면 채우기
  
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600); // 시리얼 초기화 설정
}

void draw() {
  background(0); // 배경을 검정색으로
  stroke(0, 255, 36); // 야광으로 색 설정
  arc(cx, cy, width, height, PI, TWO_PI, CHORD); // 레이더를 그려주는 거 // TWO_PI = 2*pi // CHORD = 시작과 끝 부분이 닫혀있는거
  float r = TWO_PI - map(rad, 0, 360, 0, TWO_PI);
  line(cx, cy, cx + cos(r) * width/2, cy + sin(r)*height/2); // 원 안에 있는 막대기를 사용하기 위해 사용한 공식
  updateBalls(); 
  displayBalls();
}

// balls의 사이즈를 줄이면서 없애기
void updateBalls(){
  for(int i = balls.size()-1; i > -1 ; i--){ // 앞에서부터 하면 인덱스 값 꼬여서 뒤에서부터 하는거
    balls.get(i).update(); // ball의 사이즈를 -1씩 줄임
    if(balls.get(i).isDead())
      balls.remove(i); // 크기가 0이면 없애기
  }
}

// balls 그리기
void displayBalls(){
  for(int i = 0; i < balls.size() - 1; i++){
    balls.get(i).display();
  }
}

// 시리얼 통신
void serialEvent(Serial p){
  String inString = p.readStringUntil('\n');
  if(inString != null){
    if(inString.startsWith("r")){
      String[] strings = inString.trim().replace("r","").split("d"); // trim으로 앞뒤 공백, 개행문자 제거 // replace로 r제거 // 'd'를 기준으로 쪼개기
      if(strings.length>1){ // 정상적으로 안 쪼개지면 크기가 1이 됨. // 정상적으로 쪼개진 것인지 아닌지 체크
        rad = Integer.parseInt(strings[0]); // string을 int로 전환
        int distance = Integer.parseInt(strings[1]);  
        if(distance != 0){ // 거리가 0이면 초음파센서가 펄스인해서 정상적으로 값을 못 읽었다는 거
          balls.add(new Ball(cx, cy, rad, distance));
        }
      }
    }
  }
}
