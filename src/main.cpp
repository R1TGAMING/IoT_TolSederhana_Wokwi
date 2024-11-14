#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define TRIG 13
#define ECHO 12
int num = 0;

Servo pinServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int distanceCM() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  int durasi = pulseIn(ECHO, HIGH);
  return durasi * 0.034 / 2;
}

void setDistance(float distance) {
  if (distance <= 200) {
    num += 1;
    lcd.setCursor(7, 1);
    lcd.print(num);
    return pinServo.write(0);

  } else {
    return pinServo.write(90);
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinServo.attach(6);

  //lcd.setCursor(0, 0);
  //lcd.print("JUMLAH KENDARAAN");
  //lcd.clear();
}

void loop() {
  float distance = distanceCM();

  lcd.setCursor(0,0);
  lcd.print("JUMLAH KENDARAAN");
  
  setDistance(distance);
  delay(2000);
  pinServo.write(90);
  delay(1000);
}