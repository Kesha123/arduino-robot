#include <LiquidCrystal.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
unsigned long time;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(20,4);
}

void loop() {
  float value=analogRead(A15);
  float voltage=value*5/1023;
  lcd.setCursor(0,0);
  lcd.print(voltage);
  delay(500);
}
