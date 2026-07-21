#include <Arduino.h>
#include "hcsr04.h"
#include <ESP32Servo.h>
#include "Servo.h"
#include "passive_buzzer.h"

//----------------------Pin Definitions-----------------------
// Ultrasonic
int trig = 27;
int echo = 14;
// Passive buzzer
int buzzer = 4;
// Servo
int servo = 13;

//----------------Non-blocking Buzzer------------------------
// Scan tone (high/low frequency switching)
#define BUZZER_SCAN_LOW_FREQ_HZ   880
#define BUZZER_SCAN_HIGH_FREQ_HZ  1320

// Alert tone 
#define BUZZER_ALERT_FREQ_HZ      2400

// Alert distance
#define BUZZER_ALERT_DISTANCE_CM  20.0

// Alert hold time
#define BUZZER_ALERT_HOLD_MS     600

// Buzzer state (scan and alert)
enum BuzzerState
{
    BUZZER_SCAN,
    BUZZER_ALERT
};
// Start in scan state
BuzzerState buzzer_state = BUZZER_SCAN;  
// Alert timestamp
unsigned long alert_until_ms = 0;

// Scan tone state
enum PingState
{
    PING_LOW,
    PING_LOW_OFF,
    PING_HIGH,
    PING_WAIT
};
// Start in low frequency state
PingState ping_state = PING_LOW;
// Scan timestamp
unsigned long ping_timer = 0;

// Scan high/low frequency toggle
unsigned long ping_prev_ms = 0;
bool ping_high = false;

// Buzzer output state
unsigned long buzzer_prev_ms = 0;
bool buzzer_output = false;
int buzzer_freq = 0;
int buzzer_on_ms = 80;
int buzzer_off_ms = 600;

// Buzzer state switch based on distance
void alarm_set(float dist)
{
    unsigned long now = millis();

    // Enter alert mode
    if(dist <= BUZZER_ALERT_DISTANCE_CM)
    {
        alert_until_ms = now + BUZZER_ALERT_HOLD_MS;
    }

    // Determine current state
    if(now < alert_until_ms)
    {
        buzzer_state = BUZZER_ALERT;
    }
    else
    {
        buzzer_state = BUZZER_SCAN;
    }
}

// Buzzer state update
void alarm_update()
{
    unsigned long now = millis();

    // Alert mode
    if(buzzer_state == BUZZER_ALERT)
    {

        buzzer_freq = BUZZER_ALERT_FREQ_HZ;
        buzzer_on_ms = 50;
        buzzer_off_ms = 40;
    }

    // Scan mode (dual-frequency toggle)
    else
    {
        if(now - ping_prev_ms >= 35)
        {
            ping_prev_ms = now;
            ping_high = !ping_high;
            if(ping_high)
            {
                buzzer_freq = BUZZER_SCAN_HIGH_FREQ_HZ;
            }
            else
            {
                buzzer_freq = BUZZER_SCAN_LOW_FREQ_HZ;
            }
        }
        buzzer_on_ms = 10;
        buzzer_off_ms = 25;
    }

    // Control buzzer
    if(buzzer_output)
    {
        if(now - buzzer_prev_ms >= buzzer_on_ms)
        {
            buzzer_off();
            buzzer_prev_ms = now;
            buzzer_output = false;
        }
    }
    else
    {
        if(now - buzzer_prev_ms >= buzzer_off_ms)
        {
            buzzer_on(buzzer_freq);
            buzzer_prev_ms = now;
            buzzer_output = true;
        }
    }

}
//---------------------------------------------------


// -----------------Non-blocking Servo------------------------
unsigned long servo_prev_ms = 0;    // Timestamp of last servo movement
int servo_interval_ms = 20;   // Move servo 1 degree every 20ms

unsigned long scan_prev_ms = 0;     // Timestamp of last sensor scan
int scan_interval_ms = 40;   // Read sensor and set new target every 40ms
// Note: scan_interval_ms must be greater than and divisible by servo_interval_ms
// Otherwise servo movement will be discontinuous and unable to complete a 180° sweep

int  angle       = 0;        // Current servo target angle
int  angle_step  = 2;        // Advance target by 2 degrees each step
bool forward     = true;    // Current sweep direction (0° -> 180°)

float distance = 0;         // Current measured distance

void setup()
{
    Serial.begin(115200);
    hcsr04_init(trig, echo);
    servo_init(servo);
    buzzer_init(buzzer);
}

void loop()
{
    // Get current time
    unsigned long now = millis();

    // Servo per-degree update
    if (now - servo_prev_ms >= servo_interval_ms) 
    {
        servo_prev_ms = now;    // Update servo timestamp
        servo_update();     // Update servo angle
    }

    // Update buzzer state (every loop)
    alarm_update();

    // Sensor scan + update target angle
    if (now - scan_prev_ms >= scan_interval_ms) 
    {
        scan_prev_ms = now;     // Update sensor timestamp

        distance = hcsr04_read_distance(trig, echo);
        alarm_set(distance);
        set_servo_angle(angle);

        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);

        // After each sensor scan, update target angle based on sweep direction
        if (forward) 
        {
            angle += angle_step;
            if (angle >= 180) 
            { 
                angle = 180; 
                forward = false; 
            }
        } 
        else 
        {
            angle -= angle_step;
            if (angle <= 0)   
            { 
                angle = 0;   
                forward = true;  
            }
        }
    }
}
