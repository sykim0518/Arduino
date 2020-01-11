/*************************************************************************/
/* 프로그램 : 서보모터를 연동하는 서킷 제작 과제                                */                                            */
/*  내용 :   버튼을 눌러서 서보 모터가 동작한다.                               */
/*          버튼을 길게 누르는 동안 서보 모터의 각도가 지속적으로 변동된다.        */
/*          버튼을 떼면 본래의 상태로 천천히 돌아론다.                         */
/*          버튼이 눌리는 동안은 LED가 On, 떼면 LED가 Off                     */
/* 포트번호 : 스위치 8 LED 13 서보 모터 9                                     */
/*************************************************************************/

#define led 13     
#define state 8  
#define survo 9

#include <Servo.h>

Servo myservo;

int value = 0;
int angle = 0;
bool dir = 1;

void setup() {

  pinMode(led, OUTPUT);
  pinMode(state, INPUT);
  myservo.attach(survo);
}

void loop() {

  value = digitalRead(state);

  // 버튼이 눌렸을 경우
  if (value == HIGH) {
    digitalWrite(led, HIGH); // LED 켜기
    
    if (angle >= 180) //각도가 180도 이상일 경우
    {
      angle=180
      dir=0;
    }
    
    else // 각도가 180도 미만일 경우
    {
      if(dir==1) //오른쪽 방향일 경우A
      {
        angle++;
      }
      else if(dir==0)// 왼쪽 방향일 경우
      {
        angle--;
      }
    }
    
    myservo.write(angle);
    delay(15);
  }

  // 버튼이 떼졌을 경우
  else
  {
    digitalWrite(led, LOW);    // LED 끄기
    
    if (angle<=0) //각도가 0도 이하일 경우
    {
      angle=0;
      dir=1;
    }
    
    else //각도가 0도 이상일 경우
    {
      angle--;
    }
    myservo.write(angle);
    delay(15);
  }
}
