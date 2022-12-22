#include <Wire.h>

#define Motor_L_dir_pin       7
#define Motor_R_dir_pin       8
#define Motor_L_pwm_pin       9
#define Motor_R_pwm_pin       10

#define slaveAddress 0x60

#define pulse_port_right 2
#define pulse_port_left 3

int right_wheel_pulse_count = 0;
int left_wheel_pulse_count = 0;

byte raw;
int initial_degree = -1;
int current_degree;

boolean notMovedfirst = true;
boolean notMovedsecond = true;
boolean notRotated = true;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(pulse_port_right , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_right), right_wheel_pulse, RISING);
  pinMode(pulse_port_left , INPUT);
  attachInterrupt(digitalPinToInterrupt(pulse_port_left), left_wheel_pulse, RISING);
}

void loop() {
  Wire.beginTransmission(slaveAddress);
  Wire.write(1);
  Wire.endTransmission(false);
  Wire.requestFrom(slaveAddress, 1, true);

  if (notMovedfirst) move_forward(2);
  notMovedfirst = false;

  if (Wire.available() >= 1 && notRotated) {
    raw = Wire.read();
    if (initial_degree == -1) {
      initial_degree = map(raw,0,255,0,360);
    }

    current_degree = map(raw,0,255,0,360);
    digitalWrite(Motor_R_dir_pin, 1);
    Serial.println(current_degree);
    
    if ((int) abs(current_degree - initial_degree) < 180) {
        digitalWrite(Motor_R_pwm_pin, 1);
        digitalWrite(Motor_L_pwm_pin, 1);
    }
    else {
      notRotated = false;
    }
    
  }

  right_wheel_pulse_count = 0;
  if (notMovedsecond) move_forward(20);
  notMovedsecond = false;


}

void move_forward(int distance) {
  digitalWrite(Motor_R_dir_pin, 0);
  digitalWrite(Motor_L_dir_pin, 0);
  while (right_wheel_pulse_count < 14*distance) {
    digitalWrite(Motor_L_pwm_pin, 1);
    digitalWrite(Motor_R_pwm_pin, 1);
  }
}

void right_wheel_pulse() {
  right_wheel_pulse_count++;
}

void left_wheel_pulse() {
  left_wheel_pulse_count++;
}
