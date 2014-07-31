int solenoidPin = 8;
String rawData = "no data";
int passFail = 0;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
 
  
  // initialize the digital pin as an output.
  pinMode(solenoidPin, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {
 // Serial.println("test");
    
  if (Serial.available() > 0) {
       
    passFail = Serial.parseInt();
    
    if (passFail == 1) {
      Serial.println("Passed build");
      digitalWrite(solenoidPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(80);               // wait for a second
      digitalWrite(solenoidPin, LOW);    // turn the LED off by making the voltage LOW
      delay(100);
      passFail = 0;      
  
    } else if (passFail == 2) {
      
      Serial.println("Failed build");
      passFail = 0;
    
    } else {
    
      Serial.println("OK");
    
    }
    delay(100);
  }
  
}
