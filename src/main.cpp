#include <Arduino.h>
#include <motors.h>
#include <autonomous.h>
#include <ESP32Servo.h>

Servo Servo1;


void setup()
{
  Serial.begin(115200);
  Servo1.attach(7);
  Servo1.write(0);
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
      Servo1.write(180);
    }
    if(ps2x.ButtonReleased(PSB_TRIANGLE)) {
      Servo1.write(0);
    }
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
}