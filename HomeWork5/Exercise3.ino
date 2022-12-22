#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte raw;
int degree;
#define slaveAddress 0x60

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(20,4);
}

void loop() {
  Wire.beginTransmission(slaveAddress);
  Wire.write(1);
  Wire.endTransmission(false);
  Wire.requestFrom(slaveAddress, 1, true);

  if (Wire.available() >= 1) {
    raw = Wire.read();
    degree = map(raw,0,255,0,360);
    lcd.setCursor(0,0);

    if ((0 <= degree) and (degree <= 45)) {
      lcd.print("N");
    }
    else if((45 < degree) and (degree <= 90)) {
      lcd.print("NE");
    }
    else if((90 < degree) and (degree <= 135)) {
      lcd.print("E");
    }
    else if((135 < degree) and (degree <= 180)) {
      lcd.print("SE");
    }
    else if((180 < degree) and (degree <= 225)) {
      lcd.print("S");
    }
    else if((225 < degree) and (degree <= 270)) {
      lcd.print("SW");
    }
    else if((270 < degree) and (degree <= 315)) {
      lcd.print("W");
    }
    else {
      lcd.print("NW");
    }   
    
  }

  delay(100);
  lcd.clear();
}
