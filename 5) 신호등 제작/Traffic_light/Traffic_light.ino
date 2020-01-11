#define pinCarG 13
#define pinCarY 12
#define pinCarR 11

#define pinHumanG 12
#define pinHumanR 12

#define pinHumanSw 7
#define TIME_USE_HUMAN 2 // sec

#define BLINK_COUNT 5

unsigned long prevTime;

void setup() {
  // Serial.begin(9600);

  pinMode(pinCarG, OUTPUT);
  pinMode(pinCarY, OUTPUT);
  pinMode(pinCarR, OUTPUT);

  pinMode(pinHumanG, OUTPUT);
  pinMode(pinHumanR, OUTPUT);
  pinMode(pinHumanSw, INPUT_PULLUP);

  // Serial.println("Start Traffic Sign System.");

  initLED();
}

void loop() {
  int sw = digitalRead(pinHumanSw);

  if (sw == 0 && digitalRead(pinCarG) == 1) {
    changeLED();
  } else {
    unsigned long currentTime = millis();
    if (currentTime > prevTime + 10 * 1000) {
      changeLED();
    }
  }

}
void changeLED() {
  Serial.println("Press Switch. wait 3 sec.");
  delay(1000);

  Serial.println("Turn on car yellow led during 3 sec.");

  digitalWrite(pinCarG, LOW);
  digitalWrite(pinCarY, HIGH);
  delay(2000);

  digitalWrite(pinCarY, LOW);
  digitalWrite(pinCarR, HIGH);

  digitalWrite(pinHumanR, LOW);
  digitalWrite(pinHumanG, HIGH);

  delay(TIME_USE_HUMAN * 1000);

  Serial.println("Remain 5 sec using cross line.");

  for (int i = 0; i < BLINK_COUNT; i++) {
    digitalWrite(pinHumanG, LOW);
    delay(500);
    digitalWrite(pinHumanG, HIGH);
    delay(500);

  }
  Serial.println("Reset traffic sign");
  initLED();
}
void initLED() {
  digitalWrite(pinCarG, HIGH);
  digitalWrite(pinCarY, LOW);
  digitalWrite(pinCarR, LOW);

  digitalWrite(pinHumanG, LOW);
  digitalWrite(pinHumanR, HIGH);

  prevTime = millis();
}
