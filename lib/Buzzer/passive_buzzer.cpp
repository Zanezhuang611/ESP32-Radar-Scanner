#include <Arduino.h>
#include "passive_buzzer.h"

int buzzerPin;
int channel = 8;

void buzzer_init(int pin)
{
    buzzerPin = pin;

    // Setup PWM channel
    ledcSetup(channel, 2000, 8);

    // Bind GPIO
    ledcAttachPin(buzzerPin, channel);
}

void buzzer_on(int frequency)
{
    ledcWriteTone(channel, frequency);

    // Adjust volume
    ledcWrite(channel, 64);
}

void buzzer_off()
{
    ledcWriteTone(channel, 0);
}