void setup() {
  DDRB = DDRB | B11111100;
}

void loop() {
  PORTB = B00100000;
  delay(4000);
  PORTB = B01100000;
  delay(1000);
  PORTB = B00000000;
  PORTB = B10000000;
  delay(5000);
  PORTB = B00000000;
}
