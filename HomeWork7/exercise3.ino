#include <LiquidCrystal.h>

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  Serial.begin(9600);
  Serial.println("Write something to the serial monitor.");
  lcd.begin(20,4);
}

void loop(){
  if (Serial.available() > 0){
    String message = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("content: ");  
    lcd.print(message);
    int pos_s = message.indexOf("Print");

    if (pos_s > -1){
      lcd.setCursor(0,1);
      lcd.print("Command = Print ");
      pos_s = message.indexOf(":");

      if (pos_s > -1){
        String stat = message.substring(pos_s + 1);
        if (stat == "Hi") {
          lcd.setCursor(0,2);
          lcd.print("Hi!");
        }
        else if (stat == "Hello") {
          lcd.setCursor(0,2);
          lcd.print("Hello there!");
        }
      }  
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("Print:<Hi/Hello>");
    }
  }
}
