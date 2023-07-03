#include <Wire.h>
#include "hr.h"
#include "mpuimu.h"
#include "mqtt.h"


#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif


// define two tasks for Blink & AnalogRead
void TaskMQTT( void *pvParameters );
void TaskHR( void *pvParameters );
// void TaskMPU( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  //Wire.setPins(4,5);

  mqttsetup();
  hrsetup();
  mpusetup();
  
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskMQTT
    ,  "TaskBlink"   // A name just for humans
    ,  10000  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskHR
    ,  "HR"
    ,  5000  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL);
  // xTaskCreate(
  //   TaskMPU
  //   ,  "MPU"
  //   ,  10000  // Stack size
  //   ,  NULL
  //   ,  1  // Priority
  //   ,  NULL);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskMQTT(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    mqttloop();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskHR(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    hrloop();
    mpuloop();
    vTaskDelay(10);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskMPU(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    mpuloop();
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}
