/**************************************/
/* 프로그램 이름 : 초음파 센서와 서보 모터를 이용한 서킷 만들기

   프로그램 내용 : 초음파 센서의 측정 거리에 따라서 서보 모터 각도가 변화 됨
                 - 멀어질수록 각도가 크게 벌어지도록 함가변 저항을 부착하여
                 서보 모터의 변화 각도를 제한(최소 각도는 90도)

*/
#include<Servo.h>

#define servo 9
#define echoPin 12
#define trigPin 13
#define resistor A0

Servo myservo;

float cmd = 0; // 초음파 센서의 거리를 입력받을 변수
int res = 0;   // 가변저항의 값을 정수로 받음
int res_mapping = 0;
int cmd_mapping = 0;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servo);
}

void loop() {
  cmd = check_distance();
  
  res = analogRead(A0);
  res_mapping = map(res, 0, 1023, 90, 180);
  cmd_mapping = map(cmd, 10, 20, 0, res_mapping);

  if(cmd<=10)
  {
    myservo.write(0);
  }
  else if(cmd>=20)
  {
    myservo.write(res_mapping);
  }
  else
  {
    myservo.write(cmd_mapping);
  }
  
  Serial.print("거리의 값 :");
  Serial.println(cmd);
  Serial.print("가변 저항의 값 :");
  Serial.println(res);
  Serial.print("서보모터 각도 범위 :");
  Serial.println(res_mapping);
  Serial.print("서보모터의현재각도 :");
  Serial.println(cmd_mapping);
  
  delay(50);
}

/* 초음파센서를 이용하여 거리를 측정하는 함수 */
float check_distance()
{
  float distance = 0;
  float duration = 0;

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;

  return distance;      // 계산된 거리를 리턴
}
