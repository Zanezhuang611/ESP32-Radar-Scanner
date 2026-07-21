#include <Arduino.h>
#include <ESP32Servo.h>
#include "Servo.h"

Servo myservo;
int current_angle = 0;
int target_angle = 0;

void servo_init(int servo_pin)
{
    myservo.attach(servo_pin);
    myservo.write(current_angle);
}

// Set the target angle of the servo
void set_servo_angle(int angle)
{
    target_angle = angle;
}

// Move the servo 1 degree toward the target angle each time 
void servo_update()
{
    if (current_angle < target_angle) 
    {
        current_angle++;
        myservo.write(current_angle);
    } 
    else if (current_angle > target_angle) 
    {
        current_angle--;
        myservo.write(current_angle);
    }
}
