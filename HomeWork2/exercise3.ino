#define btn 19


void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btn),isr,FALLING);
}

void loop() {
  
}

void isr() {
 	static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();  

  if (interrupt_time - last_interrupt_time > 200) {
    Serial.println("pressed");
  }
  
  last_interrupt_time = interrupt_time;
}
