#include <Arduino.h>
#include <motors.h>
#include <PS2_controller.h>

#define s1 39
#define s2 36
#define s3 2
#define s4 32
#define IRSwitch 7
#define IR 8
void setup()
{
  Serial.begin(115200);
  pinMode(s1, INPUT); //Cảm biến nhận tín hiệu
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(IRSwitch, INPUT);
  pinMode(IR,INPUT);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(false, 0);
  PS2control();
  int giatri1 = digitalRead(s1); //Đọc giá trị cảm biến s1 và gán vào biến giatri1
  int giatri2 = digitalRead(s2);
  int giatri3 = digitalRead(s3);
  int giatri4 = digitalRead(s4);
  int gtcongtac = digitalRead(IRSwitch);
  int gthongngoai = digitalRead(IR);
  
  Serial.print("S1: ");
  Serial.print(giatri1);Serial.print("   ");
  Serial.print("S2: ");
  Serial.print(giatri2);Serial.print("   ");
  Serial.print("S3: ");
  Serial.print(giatri3);Serial.print("   ");
  Serial.print("S4: ");
  Serial.print(giatri4);Serial.print("   ");
  Serial.print("Công tắc: ");
  Serial.print(gtcongtac);Serial.print("   ");
  Serial.print("Hồng ngoại: ");
  Serial.println(gthongngoai);  
  delay(200);
}