#include "Servo.h"

#define MOTOR_PIN1 4
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 7

#define GUN_PWM_MIN 1310
#define GUN_PWM_MAX 2640

#define MOTOR_PWM_MIN 900
#define MOTOR_PWM_MAX 2100

#define GUN_PIN 8

Servo powerServo[4];
int readSerial;
void setup()
{
    Serial.begin(9600);
    pinMode(GUN_PIN, INPUT);
    powerServo[0].attach(MOTOR_PIN1);
    powerServo[1].attach(MOTOR_PIN2);
    powerServo[2].attach(MOTOR_PIN3);
    powerServo[3].attach(MOTOR_PIN4);
}

void loop()
{
    unsigned long duration = 0;
    duration = pulseIn(GUN_PIN, HIGH);

    Serial.println(duration);
    motor_control(duration);
    delay(1000);
}

void motor_control(unsigned long power)
{
    int i = 0;
    long t0 = micros(); //记录进入loop的时间
    unsigned long T = 20000; // 一个周期的微秒值
    unsigned long ctrlPower = map(power, GUN_PWM_MIN,
        GUN_PWM_MAX, MOTOR_PWM_MIN, MOTOR_PWM_MAX);

    unsigned long len = ctrlPower;  //(0~200对应总周期0.9ms～1.9ms)
    Serial.print("len:");
    Serial.println(len);
    for(i = 0; i < 4; i++)
    powerServo[i].writeMicroseconds(len);

    int leftMs = (int) (t0 + T - micros());
    delayMicroseconds(leftMs);
    Serial.print("leftMs:");
    Serial.println(leftMs);
}
