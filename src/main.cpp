#include <Arduino.h>
#include <motors.h>
#include <autonomous.h>
#include <ESP32Servo.h>
#include <PS2_controller.h>

#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13

#define Servo_1 7
#define Servo_2 6
#define Servo_3 5
#define Servo_4 4
#define Servo_5 3
#define Servo_6 2

bool controlMode = true;
void setup()
{
  Serial.begin(115200);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
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
    if(ps2x.ButtonPressed(PSB_L2)) {      
      pwm.setPWM(PWM_CHANNEL5,0,4095);
      pwm.setPWM(PWM_CHANNEL6,0,4095);
    }
    if(ps2x.ButtonPressed(PSB_SQUARE)) {
      pwm.setPWMFreq(50);
      pwm.setPWM(Servo_1,0,110);
      delay(200);
      pwm.setPWM(Servo_1,0,0);
      pwm.setPWMFreq(1600);
    }
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  if(ps2x.Button(PSB_START)) {autoMode();}
  pushEngine();
}