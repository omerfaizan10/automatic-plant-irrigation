#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
int soilMoistureValue = 0;
int percentage=0;

#define Grove_Water_Sensor 9;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(Grove_Water_Sensor, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  soilMoistureValue = analogRead(A0);
  lcd.setCursor(0, 0);
  lcd.print("Moisture = ");
  lcd.print(percentage);
  lcd.print(" ");
  lcd.print("%");
  lcd.print(" ");

  percentage = map(soilMoistureValue, 490, 1023, 100, 0);
  
  if (percentage > 100) {
    percentage = 100;
  }
  
  if (percentage < 10) {
    lcd.setCursor(0, 1);
    lcd.print(" pump on");
    digitalWrite(2, LOW);
  }
  
  if (percentage > 80) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture = ");
    lcd.print(percentage);
    lcd.print(" ");
    lcd.print("%");
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("pump off");
    digitalWrite(2, HIGH);
  }
  
  delay(1000);
  
  if (digitalRead(Grove_Water_Sensor) == LOW && percentage < 10) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
