#include "Arduino.h"
#include "softwaretimer.h"
#include "fsm_2waytrafficlight.h"


#define INIT -1
#define RED_GRE 0
#define RED_YEL 1
#define GRE_RED 2
#define YEL_RED 3
#define RED_GRE_TIME 3
#define RED_YEL_TIME 2
#define GRE_RED_TIME 3
#define YEL_RED_TIME 2


int d1, d2, d3, d4;
int two_way_traffic_light_status = INIT;
int task_ID;

void twoWayTrafficLight_setTaskID(int _task_ID) {
  task_ID = _task_ID;
}

void twoWayTrafficLight_setPins(int pin1, int pin2, int pin3, int pin4) {
  d1 = pin1;
  d2 = pin2;
  d3 = pin3;
  d4 = pin4;

  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
}


void twoWayTrafficLight_Run() {
  switch (two_way_traffic_light_status) {
    case INIT:  // start the traffic light with RED_GRE status
      two_way_traffic_light_status = RED_GRE;
      setTimer(task_ID, RED_GRE_TIME);
      setLightRed(d1, d2);     // Road A = RED
      setLightGreen(d3, d4);   // Road B = GREEN
      break;

    case YEL_RED:
      if (isTimerExpired(task_ID)) {
        two_way_traffic_light_status = RED_GRE;
        setTimer(task_ID, RED_GRE_TIME);
        setLightRed(d1, d2);     // Road A = RED
        setLightGreen(d3, d4);   // Road B = GREEN
      }
      break;

    case RED_GRE:
      if (isTimerExpired(task_ID)) {
        two_way_traffic_light_status = RED_YEL;
        setTimer(task_ID, RED_YEL_TIME);
        setLightRed(d1, d2);     // Road A = RED
        setLightYellow(d3, d4);  // Road B = YELLOW
      }
      break;

    case RED_YEL:
      if (isTimerExpired(task_ID)) {
        two_way_traffic_light_status = GRE_RED;
        setTimer(task_ID, GRE_RED_TIME);
        setLightGreen(d1, d2);   // Road A = GREEN
        setLightRed(d3, d4);     // Road B = RED
      }
      break;

    case GRE_RED:
      if (isTimerExpired(task_ID)) {
        two_way_traffic_light_status = YEL_RED;
        setTimer(task_ID, YEL_RED_TIME);
        setLightYellow(d1, d2);  // Road A = YELLOW
        setLightRed(d3, d4);     // Road B = RED
      }
      break;
  }
}


void setLightOff(int ID1, int ID2) {
  digitalWrite(ID1, LOW);
  digitalWrite(ID2, LOW);
}

void setLightRed(int ID1, int ID2) {
  digitalWrite(ID1, HIGH);
  digitalWrite(ID2, HIGH);
}

void setLightGreen(int ID1, int ID2) {
  digitalWrite(ID1, HIGH);
  digitalWrite(ID2, LOW);
}

void setLightYellow(int ID1, int ID2) {
  digitalWrite(ID1, LOW);
  digitalWrite(ID2, HIGH);
}