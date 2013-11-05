/*
Title: Robot mk1 - distance sensing two-wheel-drive autonomous robot
Author: Stuart Robinson
*/

#include <Servo.h>

Servo sensorServo;

int M1direction = 12; // polarity, HIGH or LOW
int M1speed = 3; // 0-255 analogWrite
int M1brake = 9; // start (LOW) or stop (HIGH)
// int M1currentSensor = 0;

int M2direction = 13; // polarity, HIGH or LOW
int M2speed = 11; // 0-255 analogWrite
int M2brake = 8; // start (LOW) or stop (HIGH)
// int M2currentSensor = 1;

int distanceSensor = 2;
int servoPin = 6;
int distanceThreshold = 18; // 18 cm reading on distance sensor is the closest it should get

void setup() {
 
    //Setup Channel A
  
    pinMode(M1direction, OUTPUT); //Initiates Motor Channel A pin
    pinMode(M1brake, OUTPUT); //Initiates Brake Channel A pin
  
    // channel B
    pinMode(M2direction, OUTPUT); //Initiates Motor Channel A pin
    pinMode(M2brake, OUTPUT); //Initiates Brake Channel A pin
   
    sensorServo.attach(servoPin);
    sensorServo.write(75); // reposition the servo so 75 (midway point of reach) points dead ahead

    delay(12000); // delay before start to manually position properly

}

void loop() {
          
    // move forward as standard
    moveForward();
    delay(15);

    float distance = getDistance();
    
    // stop moving forward if too close to obstruction
    if(distance < distanceThreshold) {
      
        // stop both motors
        digitalWrite(M1brake, HIGH); //Eengage the Brake for Channel A
        digitalWrite(M2brake, HIGH); //Eengage the Brake for Channel B
 
        // move servo left
        sensorServo.write(0);
        delay(500);
        //get left reading
        float leftReading = getDistance();
        delay(15);
        
        // move servo right
        sensorServo.write(150);
        delay(500);
        //get left reading
        float rightReading = getDistance();
        delay(15);
            
        sensorServo.write(75); //return to center
        delay(15);
         
        if(leftReading > rightReading && leftReading > distanceThreshold) {
            turnLeft();
        } else if (rightReading > leftReading && rightReading > distanceThreshold) {
            turnRight();
        } else {
            aboutTurn();
        }
    } 
    
    delay(30);
}


void moveForward() {
  
    //forward full speed both motors
        
    digitalWrite(M1direction, LOW); //Establishes forward direction
    digitalWrite(M1brake, LOW);   //Disengage the Brake
    analogWrite(M1speed, 252);   //Spins the motor
  
    // also for motor 2
    digitalWrite(M2direction, LOW); 
    digitalWrite(M2brake, LOW);   
    analogWrite(M2speed, 255);         
}


float getDistance() {
    return 12343.85 * pow(analogRead(distanceSensor), -1.15); 
}

void turnLeft() {
  
    digitalWrite(M1direction, HIGH); //backwards motor 1
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 252);  
  
    digitalWrite(M2direction, LOW); //forwards motor 2
    digitalWrite(M2brake, LOW);   
    analogWrite(M2speed, 255);
  
    delay(630);
  
    digitalWrite(M1brake, HIGH); 
    digitalWrite(M2brake, HIGH); 
    delay(500);   
}

void turnRight() {
  
    digitalWrite(M1direction, LOW); //forwards motor 1
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 252);
        
    digitalWrite(M2direction, HIGH); //backwards motor 2
    digitalWrite(M2brake, LOW); 
    analogWrite(M2speed, 255);
    
    delay(530);
    
    digitalWrite(M1brake, HIGH); 
    digitalWrite(M2brake, HIGH); 
    delay(500);
}

void aboutTurn() {
 
    delay(6000);
   
    //move back
    digitalWrite(M1direction, HIGH); //Establishes backwards direction
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 252);  
    
    digitalWrite(M2direction, HIGH); //Establishes backwards direction
    digitalWrite(M2brake, LOW);  
    analogWrite(M2speed, 255);   
    
    delay(1000);
    
    //stop
    digitalWrite(M1brake, HIGH);
    digitalWrite(M2brake, HIGH); 
     
    //turn
    
    digitalWrite(M1direction, LOW); //Establishes forward direction of Channel A
    digitalWrite(M1brake, LOW);  
    analogWrite(M1speed, 252);
    
    digitalWrite(M2direction, HIGH); //Establishes backward direction of Channel B 
    digitalWrite(M2brake, LOW);  
    analogWrite(M2speed, 255); 
    
    delay(1100);
    
    //stop
    digitalWrite(M1brake, HIGH); //Eengage the Brake for Channel A
    digitalWrite(M2brake, HIGH); //Eengage the Brake for Channel B
    delay(500);
}
