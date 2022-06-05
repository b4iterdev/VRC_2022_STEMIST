#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s3 2
#define s4 32
#define s5 25
#define IRSwitch 7
#define IR 8

void autoMode(void) {
  bool boolsensor1;
  bool boolsensor2;
  bool boolsensor3;
  bool boolsensor4;
  bool boolsensor5;
  bool boollineSwitch;
  bool boolIRSwitchval;
  if (digitalRead(s1) == 0) {boolsensor1=0;}
  else if (digitalRead(s1) == 1) {boolsensor1 = 1;}
  else if (digitalRead(s2) == 0) {boolsensor2 = 0;}
  else if (digitalRead(s2) == 1) {boolsensor2 = 1;}
  else if (digitalRead(s2) == 1) {boolsensor2 = 1;}
  else if (digitalRead(s3) == 0) {boolsensor3 = 0;}
  else if (digitalRead(s3) == 1) {boolsensor3 = 1;}
  else if (digitalRead(s4) == 0) {boolsensor4 = 0;}
  else if (digitalRead(s4) == 1) {boolsensor4 = 1;}
  else if (digitalRead(s5) == 0) {boolsensor5 = 0;}
  else if (digitalRead(s5) == 1) {boolsensor3 = 1;}
  
  Serial.print("S1: ");
  Serial.print(boolsensor1);Serial.print("   ");
  Serial.print("S2: ");
  Serial.print(boolsensor2);Serial.print("   ");
  Serial.print("S3: ");
  Serial.print(boolsensor3);Serial.print("   ");
  Serial.print("S4: ");
  Serial.print(boolsensor4);Serial.print("   ");
  Serial.print("Công tắc: ");
  Serial.print(boollineSwitch);Serial.print("   ");
  Serial.print("Hồng ngoại: ");
  Serial.println(boolIRSwitchval);  

  bool cStatus[5] = {boolsensor1,boolsensor2,boolsensor3,boolsensor4,boolsensor5};
  if (cStatus[3] && cStatus[2] && cStatus[4] == 0) {
    //forward
  } else if (cStatus[3] && cStatus[2] && !cStatus[4] == 0) {
    //turn left
  } else if (cStatus[3] && !cStatus[2] && cStatus[4] == 0) {
    //turn right
  }
}