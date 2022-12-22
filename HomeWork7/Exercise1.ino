#include <LiquidCrystal.h>

#define VRX A8
#define VRY A9

#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

#define pulse_port_right 2
#define pulse_port_left 3

const int rs = 37, en = 36, d4 = 35, d5 = 34, d6 = 33, d7 = 32;

int right_wheel_pulse_count = 0;
int left_wheel_pulse_count = 0;

float yDirection;
float xPower;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
  pinMode(pulse_port_right , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_right), right_wheel_pulse, RISING);
  pinMode(pulse_port_left , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_left), left_wheel_pulse, RISING);
}


void loop() {

  int xValue = analogRead(VRX);
  int yValue = analogRead(VRY);

  yDirection = (float) yValue/1024;
  xPower = (float) xValue/1024;

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
  lcd.print("Right: " + String((float) right_wheel_pulse_count/14, 2));
  lcd.setCursor(0,1);
  lcd.print("Left:  " + String((float) left_wheel_pulse_count/14, 2));
}


void right_wheel_pulse() {
  if (xPower < 0.48) {
    right_wheel_pulse_count++;
  }
  else if (xPower > 0.52) {
    right_wheel_pulse_count--;
  }
}

void left_wheel_pulse() {
  if (xPower < 0.48) {
    left_wheel_pulse_count++;
  }
  else if (xPower > 0.52) {
    left_wheel_pulse_count--;
  }
}
