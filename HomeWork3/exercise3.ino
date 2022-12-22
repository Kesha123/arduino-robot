#define btn 19

#define redLED 11
#define greenLED 13

boolean switcher = false;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btn),isr,FALLING);
}

void loop() {
  
}

void isr() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();  

  if (interrupt_time - last_interrupt_time > 200) {
    switcher = !switcher;
    if (switcher) {
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, HIGH);
    }
    else {
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, LOW);
    }
  }
  
  last_interrupt_time = interrupt_time;
}
