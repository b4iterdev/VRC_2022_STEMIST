#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2_controller.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13

void pushEngine(void) {
    if (ps2x.Button(PSB_CROSS)) { // Trả về giá trị TRUE khi nút được thay đổi trạng thái
    pwm.setPWM(PWM_CHANNEL5,4095,0);
    } else {
    pwm.setPWM(PWM_CHANNEL5,4095,4095);
    }
    if(ps2x.Button(PSB_CIRCLE)) {
    pwm.setPWM(PWM_CHANNEL5,0,4095);
    } else {
    pwm.setPWM(PWM_CHANNEL5,4095,4095);
    }

}