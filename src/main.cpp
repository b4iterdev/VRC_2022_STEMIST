#include <Arduino.h>
#include <motors.h>
#include <autonomous.h>
#include <ESP32Servo.h>
#include <PS2_controller.h>

#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13


void setup()
{
  Serial.begin(115200);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(IRSwitch, INPUT);
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
      pwm.setPWM(PWM_CHANNEL6,4095,0);
      pwm.setPWM(PWM_CHANNEL5,0,4095);
      delay(3000);
      pwm.setPWM(PWM_CHANNEL5,2048,2048);
      pwm.setPWM(PWM_CHANNEL6,2048,2048);
    }
    if(ps2x.ButtonPressed(PSB_CROSS)) {
       
    }
    if(ps2x.ButtonPressed(PSB_SQUARE)) {
    }
    
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  //if(ps2x.Button(PSB_START)) {autoMode();}
  pushEngine();
}