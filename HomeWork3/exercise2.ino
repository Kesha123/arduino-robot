#define VRX A8
#define VRY A9

#define redLED 11
#define greenLED 13

float brightness = 0;
float ledDirection = 0;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  int xValue = analogRead(VRX);
  int yValue = analogRead(VRY);

  brightness = convert(yValue);
  ledDirection = (float) xValue/1024;

  analogWrite(greenLED, ledDirection*brightness);
  analogWrite(redLED, (1 - ledDirection)*brightness);
  
  delay(10);
}

int convert(float value) {
  return value*255/1024;  
}
