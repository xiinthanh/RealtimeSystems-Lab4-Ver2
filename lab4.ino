#include "scheduler.h"
#include "softwaretimer.h"
#include "fsm_ex1.h"
#include "fsm_2waytrafficlight.h"

#include <Arduino.h>

#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

void TIMER_ISR(void *pvParameters)
{
    while (1)
    {
        SCH_Update();
        vTaskDelay(10);
    }
}

void setup()
{
    // put your setup code here, to run once:
    Ex1_SetLedPin(LED_PIN); // Set the LED pin
    twoWayTrafficLight_setTaskID(1);
    twoWayTrafficLight_setPins(D3, D4, D5, D6);

    xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

    SCH_Init();
    // SCH_Add_Task(test_blinky, 0, 100);

    SCH_Add_Task(timerRun, 0, 100);         // Add the timer run task (1 second cycle)
    SCH_Add_Task(Ex1_LedStateMachine, 0, 1); // Add the LED state machine task
    SCH_Add_Task(twoWayTrafficLight_Run, 0, 1);
}

void loop()
{
    SCH_Dispatch_Tasks();
}