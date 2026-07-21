#ifndef SERVO_H
#define SERVO_H

// Initialize the servo motor
void servo_init(int servo_pin);

// Set the target angle of the servo motor
void set_servo_angle(int angle);

// Update the servo position gradually toward the target angle
void servo_update();

#endif