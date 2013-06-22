/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 3;

int ledRed = 13;
int ledGreen = 9;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
   pinMode(ledRed, OUTPUT);   
    pinMode(ledGreen, OUTPUT);
 digitalWrite(ledGreen, LOW);
digitalWrite(ledRed, LOW); 
}

void loop() {
  if (irrecv.decode(&results)) {
  //  Serial.println(results.value, HEX);
    
    String code = String(results.value, HEX);
    
    Serial.println(code);
      
    String redCode = "2fd926d";
    String greenCode ="2fd12ed";
    
    
    if(code == redCode) {
        digitalWrite(ledGreen, LOW);
          digitalWrite(ledRed, HIGH);
      // turn on red led      
    } else if(code == greenCode) {
     // turn on green led
      digitalWrite(ledRed, LOW);
          digitalWrite(ledGreen, HIGH);
    }
    irrecv.resume(); // Receive the next value
  }
}
