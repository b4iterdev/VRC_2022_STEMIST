#include <Arduino.h>
#include <motors.h>
#include <autonomous.h>
#include <PS2_controller.h>

#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15

#define Servo_1 7
#define Servo_2 6
#define Servo_3 5
#define Servo_4 4
#define Servo_5 3
#define Servo_6 2

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s4 32
#define s5 25
#define IR 2

int check = 0;
int right;
int startOnBot;
int stop = 0;
bool start = true;

void setup()
{
  Serial.begin(115200);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(IR,INPUT);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void pushEngine(void) {
    if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
      pwm.setPWM(PWM_CHANNEL5,4095,0);
      pwm.setPWM(PWM_CHANNEL6,0,4095);
    }
    if(ps2x.ButtonPressed(PSB_CIRCLE)) {
      pwm.setPWM(PWM_CHANNEL5,0,4095);
      pwm.setPWM(PWM_CHANNEL6,4095,0);    
    }
    if(ps2x.ButtonPressed(PSB_R1)) {
      pwm.setPWM(PWM_CHANNEL7,4095,0);
      pwm.setPWM(PWM_CHANNEL8,0,4095);
    }
    if(ps2x.ButtonPressed(PSB_R2)) {
      pwm.setPWM(PWM_CHANNEL7,0,4095);
      pwm.setPWM(PWM_CHANNEL8,4095,0); 
    }
    if(ps2x.ButtonPressed(PSB_L2)) {      
      pwm.setPWM(PWM_CHANNEL5,0,4095);
      pwm.setPWM(PWM_CHANNEL6,0,4095);
      pwm.setPWM(PWM_CHANNEL7,0,4095);
      pwm.setPWM(PWM_CHANNEL8,0,4095);
    }
    if(ps2x.ButtonPressed(PSB_SQUARE)) {
      pwm.setPWMFreq(50);
      pwm.setPWM(Servo_1,0,110);
      pwm.setPWM(Servo_2,0,110);
      pwm.setPWM(Servo_3,0,110);
      pwm.setPWM(Servo_4,0,110);
      delay(200);
      pwm.setPWM(Servo_1,0,0);
      pwm.setPWM(Servo_2,0,0);
    }
    if(ps2x.ButtonPressed(PSB_CROSS)) {
      pwm.setPWMFreq(50);
      pwm.setPWM(Servo_1,0,224);
      pwm.setPWM(Servo_2,0,224);
      pwm.setPWM(Servo_3,0,110);
      pwm.setPWM(Servo_4,0,110);
      delay(200);
      pwm.setPWM(Servo_1,0,0);
      pwm.setPWM(Servo_2,0,0);
    }
    if(ps2x.ButtonPressed(PSB_L1)) {      
      pwm.setPWM(Servo_1,0,0);
      pwm.setPWM(Servo_2,0,0);
      pwm.setPWM(Servo_3,0,0);
      pwm.setPWM(Servo_4,0,0);
      delay(200);
      pwm.setPWMFreq(1600);
     }
}
void autoMode(void) {
  unsigned long startTimer = millis();
  while(start == true) {
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

  if(millis() - startTimer >= 20000) {
    break;
  }
  if(ps2x.ButtonPressed(PSB_SELECT)) {stop = 1;}
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
  } else if(stop == 1) {break;}
  while(startOnBot == 1) {Serial.println("The device is set to start from the bottom line.");}
  while(right == 1) {Serial.println("The device is set to start from right");}
  }
}
void getInfo() {
  if(ps2x.ButtonPressed(PSB_PAD_DOWN)) {startOnBot = 1;}
  if(ps2x.ButtonPressed(PSB_PAD_UP)) {startOnBot = 0;}
  if(ps2x.ButtonPressed(PSB_PAD_LEFT)) {right = 0;}
  if(ps2x.ButtonPressed(PSB_PAD_RIGHT)) {right = 1;}
  if(ps2x.ButtonPressed(PSB_START)) {autoMode();}
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  getInfo();
  Serial.print(startOnBot);
  Serial.println(right);
  pushEngine();
}