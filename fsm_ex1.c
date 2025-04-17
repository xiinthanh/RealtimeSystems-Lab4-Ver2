#include "softwaretimer.h"
#include "Arduino.h"
#include "fsm_ex1.h"


#define INIT 0
#define LED_ON 1
#define LED_OFF 2
#define T_ON 1  // 1 second
#define T_OFF 1 // 1 second


int led_pin = 48;
int led_status = INIT;

#ifdef __cplusplus
extern "C"
{
#endif

void Ex1_SetLedPin(int pin)
{
    // Set the pin as output
    led_pin = pin;
}
void Ex1_OpenLedPin()
{
    // Open the LED pin
    pinMode(led_pin, OUTPUT);
}
void Ex1_TurnLedOn()
{
    // Turn the LED on
    led_status = LED_ON;
    digitalWrite(led_pin, HIGH);
}
void Ex1_TurnLedOff()
{
    // Turn the LED off
    led_status = LED_OFF;
    digitalWrite(led_pin, LOW);
}
void Ex1_LedStateMachine()
{
    switch (led_status)
    {
    case INIT:
        // Initialize the LED pin: turn on LED
        Ex1_OpenLedPin();
        Ex1_TurnLedOn();
        setTimer(0, T_ON);
        break;
    case LED_ON:
        if (isTimerExpired(0))
        {
            // If the timer has expired, turn the LED off
            Ex1_TurnLedOff();
            setTimer(0, T_OFF); // Set a timer
        }
        break;
    case LED_OFF:
        if (isTimerExpired(0))
        {
            // If the timer has expired, turn the LED on
            Ex1_TurnLedOn();
            setTimer(0, T_ON); // Set a timer
        }
        break;
    default:
        break;
    }
}

#ifdef __cplusplus
}
#endif
