#include <LiquidCrystal.h>

#define VRX A8
#define VRY A9

#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

#define port 2

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;

int right_wheel_pulse_count = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(20,4);
  pinMode(port , INPUT);
  attachInterrupt(digitalPinToInterrupt(port), right_wheel_pulse, RISING);
}


void loop() {

  int xValue = analogRead(VRX);
  int yValue = analogRead(VRY);

  float yDirection = (float) yValue/1024;
  float xPower = (float) xValue/1024;

  if (xPower < 0.48) {
    digitalWrite(Motor_R_dir_pin, 0);
    digitalWrite(Motor_L_dir_pin, 0);
  }
  else if (xPower > 0.52) {
    digitalWrite(Motor_R_dir_pin, 1);
    digitalWrite(Motor_L_dir_pin, 1);
  }

  if (xPower >= 0.48 && xPower <= 0.52) {
    analogWrite(Motor_L_pwm_pin, 0);
    analogWrite(Motor_R_pwm_pin, 0);
  }
  else {
    analogWrite(Motor_L_pwm_pin, yDirection*255);
    analogWrite(Motor_R_pwm_pin, (1-yDirection)*255);
  }
  
  lcd.setCursor(0,0);
  lcd.print(right_wheel_pulse_count);
}


void right_wheel_pulse() {
  right_wheel_pulse_count++;
}
