#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s3 2
#define s4 32
#define s5 25
#define IR 0

bool start = true;
int check = 0;
int right;
int startOnBot;

void autoMode(void) {
  while(start == true) {
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

  if (ps2x.ButtonPressed(PSAB_PAD_UP)) {startOnBot = 0;}
  else if (ps2x.ButtonPressed(PSAB_PAD_DOWN)) {startOnBot = 1;}
  else if (ps2x.ButtonPressed(PSAB_PAD_LEFT)) {right = 0;}
  else if (ps2x.ButtonPressed(PSAB_PAD_RIGHT)) {right = 1;}
  int cStatus[4] = {sen1,sen2,sen4,sen5};
  if (cStatus[2] == 0 && cStatus[1] == 0 && cStatus[0] == 0 && cStatus[3] == 1) {
    //turn left (hard)
    Serial.println("left");
    setPWMMotors(512,0,615,0);
  } else if (cStatus[2] == 0 && cStatus[1] == 0 && cStatus[0] == 1 && cStatus[3] == 1) {
    //forward
    Serial.println("forward");
    setPWMMotors(512, 0, 512, 0);
  } else if (cStatus[2] == 0 && cStatus[1] == 0 && cStatus[0] == 1 && cStatus[3] == 0) {
   //turn right (hard)
    Serial.println("right");
    setPWMMotors(615,0,512,0);
  } else if (cStatus[0] == 1 && cStatus [1] == 1 && cStatus[2] == 0 && cStatus [3] == 1) {
    //turn left light
    Serial.println("left light");
    setPWMMotors(512,0,590,0);
  } else if (cStatus[0] == 1 && cStatus [1] == 0 && cStatus[2] == 1 && cStatus [3] == 1) {
    //turn right light
    Serial.println("right light");
    setPWMMotors(590,0,512,0);
  } else if(irval == 1) {
    //stop and push.
    Serial.println("stop");
    setPWMMotors(0, 0, 0, 0);
    break;
  }
  }
}