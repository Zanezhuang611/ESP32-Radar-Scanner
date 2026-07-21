#include <Arduino.h>
#include "hcsr04.h"

void hcsr04_init(int trigPin, int echoPin)
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Set trigger pin to LOW initially
    digitalWrite(trigPin, LOW);
}

float hcsr04_read_distance(int trigPin, int echoPin)
{
    // Send ultrasonic pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

     // Read the duration of the echo pulse
    long duration = pulseIn(echoPin, HIGH);

     // Calculate distance (unit: cm)
    float distance = (duration * 0.0343) / 2;

    return distance;
}