#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s3 2
#define s4 32
#define s5 25
#define IR 0

void autoMode(void) {
  int sen1 = digitalRead(s1);
  int sen2 = digitalRead(s2);
  int sen3 = digitalRead(s3);
  int sen4 = digitalRead(s4);
  int sen5 = digitalRead(s5);
  int irval = digitalRead(IR);

  Serial.print("S1: ");
  Serial.print(sen1);Serial.print("   ");
  Serial.print("S2: ");
  Serial.print(sen2);Serial.print("   ");
  Serial.print("S3: ");
  Serial.print(sen3);Serial.print("   ");
  Serial.print("S4: ");
  Serial.print(sen4);Serial.print("   ");
  Serial.print("Công tắc: ");
  Serial.print(sen5);Serial.print("   ");
  Serial.print("Hồng ngoại: ");
  Serial.println(irval);  

  int cStatus[5] = {sen1,sen2,sen3,sen4,sen5};
  if (cStatus[3] == 0 && cStatus[1] == 0 && cStatus[2] == 0 && cStatus[0] == 0 && cStatus[4] == 1) {
    //turn left
    Serial.println("left");
  } else if (cStatus[3] == 0 && cStatus[1] == 0 && cStatus[2] == 0 && cStatus[0] == 1 && cStatus[4] == 1) {
    //forward
    Serial.println("forward");

  } else if (cStatus[3] == 0 && cStatus[1] == 0 && cStatus[2] == 0 && cStatus[0] == 1 && cStatus[4] == 0) {
   //turn right
    Serial.println("right");
  } else if(irval == 0) {
    //stop and push.
    Serial.println("right");
  }
}