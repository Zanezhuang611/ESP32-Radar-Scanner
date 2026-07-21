#ifndef BUZZER_WU_H
#define BUZZER_WU_H

// Initialize buzzer
void buzzer_init(int buzzer_pin);

// Turn on buzzer with specified frequency
void buzzer_on(int frequency);

// Turn off buzzer
void buzzer_off();

#endif