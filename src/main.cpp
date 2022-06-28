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
    if(ps2x.ButtonReleased(PSB_TRIANGLE)) {
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
      pwm.setPWM(Servo_1,0,80);
      pwm.setPWM(Servo_2,0,440);
      pwm.setPWM(Servo_3,0,80);
      pwm.setPWM(Servo_4,0,440);
    }
    if(ps2x.ButtonPressed(PSB_CROSS)) {
      pwm.setPWM(Servo_1,0,440);
      pwm.setPWM(Servo_2,0,80);
      pwm.setPWM(Servo_3,0,80);
      pwm.setPWM(Servo_4,0,440);
    }
    if(ps2x.ButtonPressed(PSB_L1)) { 
      pwm.setPWM(Servo_3,0,0);
      pwm.setPWM(Servo_4,0,0);
      delay(200);
      pwm.setPWMFreq(1600);
     }
}
void autoModePush() {
    long long startTimer = millis();
    setPWMMotors(0, 0, 0, 0);
    pwm.setPWM(PWM_CHANNEL7,4095,0);
    pwm.setPWM(PWM_CHANNEL8,0,4095);
    if(millis() - startTimer >= 200) {
      pwm.writeMicroseconds(Servo_1,1);
      pwm.writeMicroseconds(Servo_2,1);
      pwm.writeMicroseconds(Servo_3,1);
      pwm.writeMicroseconds(Servo_4,1.5);
    } else if(millis() - startTimer >= 3000) {
      pwm.setPWM(PWM_CHANNEL7,0,4095);
      pwm.setPWM(PWM_CHANNEL8,0,4095);
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
  if(ps2x.ButtonPressed(PSB_SELECT)) {start = false;}

  int cStatus[4] = {sen1,sen2,sen4,sen5}; 
  if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 1 && cStatus[3] == 0) {
    //turn left (hard)
    long long turnTimer = millis();
    if (millis() - turnTimer <= 1000)
    {
      Serial.print("backwarding");
      setPWMMotors(0,200,0,200);
      break;
    }
    Serial.println("left");
    setPWMMotors(512,0,615,0);
  
  } else if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 0 && cStatus[3] == 0) {
    //forward
    Serial.println("forward");
    setPWMMotors(512, 0, 512, 0);
  } else if (cStatus[2] == 1 && cStatus[1] == 1 && cStatus[0] == 0 && cStatus[3] == 1) {
   //turn right (hard)
   long long turnTimer = millis();
    if (millis() - turnTimer <= 1000)
    {
      Serial.print("backwarding");
      setPWMMotors(0,200,0,200);
      break;
    }
    Serial.println("right");
    setPWMMotors(615,0,512,0);
  } else if (cStatus[0] == 0 && cStatus [1] == 0 && cStatus[2] == 1 && cStatus [3] == 0) {
    //turn left light
    long long turnTimer = millis();
    if (millis() - turnTimer <= 1000) {
      Serial.print("backwarding");
      setPWMMotors(0,200,0,200);
      break;
    }
    Serial.println("left light");
    setPWMMotors(512,0,590,0);
  } else if (cStatus[0] == 0 && cStatus [1] == 1 && cStatus[2] == 0 && cStatus [3] == 0) {
    //turn right light
    Serial.println("right light");
    setPWMMotors(590,0,512,0);
  } else if(cStatus[0] == 1 && cStatus[1] == 1 && cStatus[2] == 1 && cStatus[3] == 1) {
    //stop and push.
    Serial.println("stop");
    autoModePush();
    break;
  } else if(start = false) {break;}
  }
}
void spoolauto() {
  long long startTimer = millis();
  if (millis() - startTimer <= 2000) {
  setPWMMotors(4096,0,4096,0);
  } else {setPWMMotors(0,4096,0,4096);
  delay(2000);
  }
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    //changeSpeed();
  } else if(ps2x.ButtonReleased(PSB_SELECT)) {
    spoolauto();
  }
  pushEngine();
}