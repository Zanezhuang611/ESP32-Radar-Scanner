#ifndef HCSR04_H
#define HCSR04_H

// Initialize the HC-SR04 ultrasonic sensor
void hcsr04_init(int trigPin, int echoPin);

// Read distance measured by the HC-SR04 sensor (unit: cm)
float hcsr04_read_distance(int trigPin, int echoPin);

#endif