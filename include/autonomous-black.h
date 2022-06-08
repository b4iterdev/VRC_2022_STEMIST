#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s4 32
#define s5 25
#define IR 2

int check = 0;
int right;
int startOnBot;

void autoMode(void) {
  for(int i = 0; i >= 0; i++) {
  int sen1 = digitalRead(s1);
  int sen2 = digitalRead(s2);
  int sen4 = digitalRead(s4);
  int sen5 = digitalRead(s5);
  int irval = digitalRead(IR);

  Serial.print("S1: ");
  Serial.print(sen1);Serial.print("   ");
  Serial.print("S2: ");
  Serial.print(sen2);Serial.print("   ");
  Serial.print("S4: ");
  Serial.print(sen4);Serial.print("   ");
  Serial.print("Công tắc: ");
  Serial.print(sen5);Serial.print("   ");
  Serial.print("Hồng ngoại: ");
  Serial.println(irval);  

  int cStatus[4] = {sen1,sen2,sen4,sen5};
  if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 1 && cStatus[3] == 0) {
    //turn left (hard)
    Serial.println("left");
  } else if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 0 && cStatus[3] == 0) {
    //forward
    Serial.println("forward");
    setPWMMotors(512, 0, 512, 0);
  } else if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 0 && cStatus[3] == 1) {
   //turn right (hard)
    Serial.println("right");
  } else if (cStatus[0] == 0 && cStatus [1] == 0 && cStatus[2] == 1 && cStatus [3] == 0) {
    //turn left light
    Serial.println("left light");
  } else if (cStatus[0] == 0 && cStatus [1] == 1 && cStatus[2] == 0 && cStatus [3] == 0) {
    //turn right light
    Serial.println("right light");
  } else if(irval == 1) {
    //stop and push.
    Serial.println("stop");
    setPWMMotors(0, 0, 0, 0);
    break;
  }
  }
}