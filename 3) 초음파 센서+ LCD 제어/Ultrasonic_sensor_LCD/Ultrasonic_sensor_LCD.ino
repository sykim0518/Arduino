/**************************************/
/* 프로그램 이름 : 거리측정기

   프로그램 내용 : 초음파센서를 이용하여 거리를 구하고
   구한 거리를 LCD 패널을 통해 출력해줍니다.

*/

#include <LiquidCrystal.h>

#define echoPin 12
#define trigPin 13

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD가 연결된 핀을 설정한다.

float cmd = 0;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);                      // LCD의 크기를 설정한다.
  lcd.print("Distance ?");          // LCD에 출력할 내용을 설정한다.
}

void loop() {
  cmd  = check_distance();
  Serial.println(cmd);
  tone(8, 120, 20);
  delay(100);
  noTone(8);

  delay(2.5 * cmd);
  
  Serial.print("loop문에서의 출력입니다 :");
  if (cmd >= 500 || cmd <= 2)
  {
    Serial.println("센서 인식의 범위를 초과하였습니다.");
    lcd.setCursor(1, 1);
    lcd.print("Error!");
  }
  else if(cmd <= 100)
  {
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Danger!");
  }
  else
  {
    lcd.setCursor(1, 1);
    lcd.print(cmd);
    lcd.setCursor(10, 1);
    lcd.print("cm");
  }

  delay(500);

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
