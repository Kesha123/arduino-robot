void setup(){
  Serial.begin(9600);
  Serial.println("Write something to the serial monitor.");
}

void loop(){
  if (Serial.available() > 0){
    String message = Serial.readStringUntil('\n'); 
    Serial.print("Message received, content: ");  
    Serial.println(message);
    int pos_s = message.indexOf("Print");

    if (pos_s > -1){
      Serial.println("Command = Print ");
      pos_s = message.indexOf(":");

      if (pos_s > -1){
        String stat = message.substring(pos_s + 1);
        if (stat == "Hi") {
          Serial.println("Hi!");
        }
        else if (stat == "Hello") {
          Serial.println("Hello there!");
        }
      }  
    }
    else{
	    Serial.println("No greeting found, try typing Print:Hi or Print:Hello\n");
    }
  }
}
