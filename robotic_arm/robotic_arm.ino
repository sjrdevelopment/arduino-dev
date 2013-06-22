// Robotic arm
//Incudes trunk, arm and claw servos.
#include <Servo.h>

Servo trunkServo;
Servo armServo;
Servo clawServo;

int trunkPin = 11;
int armPin = 8;
int clawPin = 7;

int incomingByte = 0;   // for incoming serial data

int toWriteTrunk = 90;
int toWriteArm = 90;
int toWriteClaw = 90;

int currentTrunk = 90;
int currentArm = 90;
int currentClaw = 90;

String rawData = "no data";

void setup()
{
  trunkServo.attach(trunkPin);
  trunkServo.write(90);
  
  armServo.attach(armPin);
  armServo.write(90);
  
  clawServo.attach(clawPin);
  clawServo.write(90);
  
  Serial.begin(9600);
  Serial.setTimeout(5000);
}

void loop()
{
   if (Serial.available() > 0) {
        

       
   toWriteTrunk = Serial.parseInt();

   toWriteArm = Serial.parseInt();

   toWriteClaw = Serial.parseInt();

  
   if(toWriteTrunk != currentTrunk && toWriteArm > 0){
     currentTrunk = toWriteTrunk;
     trunkServo.write(toWriteTrunk); 
   } else if(toWriteArm != currentArm && toWriteArm > 0){
     currentArm = toWriteArm;
     armServo.write(toWriteArm); 
   }
   

   else if(toWriteClaw != currentClaw && toWriteClaw > 0){
     currentClaw = toWriteClaw;
     clawServo.write(toWriteClaw); 
   }
   
    //  trunkServo.write(inputLevelConst); 
    //  armServo.write(inputLevelConst);
    //  clawServo.write(inputLevelConst);
  } 

}

