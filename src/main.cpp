#include <Arduino.h>
#include <motors.h>
#include <PS2_controller.h>

//Đặt chân cảm biến dò đường
#define s1 39
#define s2 36
#define s3 2
#define s4 32
#define IRSwitch 7
#define IR 8
void setup()
{
  Serial.begin(115200);
  pinMode(s1, INPUT); 
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(IRSwitch, INPUT);
  pinMode(IR,INPUT);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void lineMonitoring(void) {
  int sensor1 = digitalRead(s1);
  int sensor2 = digitalRead(s2);
  int sensor3 = digitalRead(s3);
  int sensor4 = digitalRead(s4);
  int lineSwitch = digitalRead(IRSwitch);
  int IRSwitchval = digitalRead(IR);
  
  Serial.print("S1: ");
  Serial.print(sensor1);Serial.print("   ");
  Serial.print("S2: ");
  Serial.print(sensor2);Serial.print("   ");
  Serial.print("S3: ");
  Serial.print(sensor3);Serial.print("   ");
  Serial.print("S4: ");
  Serial.print(sensor4);Serial.print("   ");
  Serial.print("Công tắc: ");
  Serial.print(lineSwitch);Serial.print("   ");
  Serial.print("Hồng ngoại: ");
  Serial.println(IRSwitchval);  
  delay(200);
}
void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  lineMonitoring();
}