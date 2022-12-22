#include <LiquidCrystal.h>

#define VRX A8
#define VRY A9

const lcdX = 20;
const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int xValue = 0;
int cursorX = 0;

void setup() {
  lcd.begin(20,4);
}

void loop() {
  xValue = analogRead(VRX);

	lcd.setCursor(0,0);
	lcd.print(float xValue*5/1023);
	
	lcd.setCursor(0,2);
	lcd.print("-100%");
	lcd.setCursor(10,2);
	lcd.print("0%");
	lcd.setCursor(13,2);
	lcd.print("+100%");
	
	cursorX = xValue*20/1023;
	lcd.setCursor(cursorX,2);
	lcd.print("I");
	
  
  delay(100);
}

