#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);

void setup() {  
  
  Serial.begin(9600);

  mySerial.begin(9600);  
}

void loop() {
    
  String c;
  
  c.reserve(200);
  
  if (mySerial.available()) {
    c = mySerial.readString();
    Serial.println("Input: " + c);
  }

}
