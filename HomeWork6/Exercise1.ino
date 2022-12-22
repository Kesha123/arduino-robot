#define VRX A8
#define VRY A9

#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

float yRotation = 0;
float xDirection = 0;

void setup() {
  Serial.begin(9600);
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

}
