class Ball{
  int life = 50;
  float x, y;
  
  public Ball(float cx, float cy, int rad, int distance){ //초기화 생성자 부분
    float d = map(distance, 0, 100, 0, width/2);
    float r = TWO_PI - map(rad, 0, 360, 0, TWO_PI); //각도와 거리를 이용해서 위치를 계산
    x = cy + cos(r) * d;
    y = cy + sin(r) * d; // ball의 x, y 좌표 설정
  }
  
  public void display(){
    ellipse(x,y,life,life); // 원 그리기. // x, y를 중심으로 life, life의 너비와 높이를 가지는 원 그리기
  }
  
  public void update(){
    --life;
    if(life<0)
    life = 0;
  }
  
  public boolean isDead(){
    return life == 0;
  }
}
