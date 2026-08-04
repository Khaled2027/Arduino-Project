#include <SimpleDHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const int rs = 7, en = 6, d4 = 8, d5 = 9, d6 = 12, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo;
int Buzzer = 2;
int pinDHT11 = 3;
byte data;
SimpleDHT11 dht11(pinDHT11);
int SIGNAL_PIN = A3;
int value = 0;
#define ENABLE 13
#define DIRA 4
#define DIRB 10

int i;

void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(Buzzer, OUTPUT);
  myservo.attach(5);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  data = dht11.read(&temperature, &humidity, NULL);
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print((int)temperature);
  lcd.print(" *C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print((int)humidity);
  lcd.print(" %");
  delay(2000);

  if (temperature > 22) {
    myservo.write(180);
    for (i = 255; i > 100; i--) {
      digitalWrite(DIRA, HIGH); //one way
      digitalWrite(DIRB, LOW);
      analogWrite(ENABLE, i); //enable on
      delay(200);
    }
    tone(Buzzer, 200);
    delay(3000);
    noTone(Buzzer);
    delay(2000);

  } else {
    myservo.write(0);
    noTone(Buzzer);
  }
  
  value = analogRead(SIGNAL_PIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water level: ");
  lcd.print(value);
  Serial.print("Water level: ");
  Serial.println(value);

  if (value >= 700) {
    tone(Buzzer, 200);
    delay(3000);
    noTone(Buzzer);
    delay(3000);
    tone(Buzzer, 200);
    delay(3000);
    noTone(Buzzer);
    delay(3000);
  }
}