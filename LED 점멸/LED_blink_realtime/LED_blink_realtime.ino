/*************************************************************************/
/* 프로그램 : LED와 BUTTON을 이용한 점멸 과제                                */                                            */
/*  내용 :   아두이노에 버튼과 LED를 부착하여 동작하는 회로를 만든다
            버튼을 누를 경우 LED가 점멸 되도록 한다
            버튼을 뗄 경우 LED는 OFF가 된다
            LED 점멸 인터벌은 0.5초로 한다
                    */
/* 포트번호 : 버튼 8 LED 13                                                */
/*************************************************************************/

#define LED 13
#define BTN 8

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
}

void loop()
{
  int value=digitalRead(BTN);
  if(value==HIGH)
  {
    if(millis()%1000>500)
      digitalWrite(LED,HIGH);
    else
      digitalWrite(LED,LOW);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
}
