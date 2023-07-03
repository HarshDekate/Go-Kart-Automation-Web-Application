//#include <sd_defines.h>

#include <TinyGPS++.h>
#include <TinyGPSPlus.h>



#include "mqtt.h"
#include "camera.h"
#include "gps.h"



#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 33
#endif

//SoftwareSerial ss1(13,12);


// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskMqttSubscribe( void *pvParameters );
void TaskGPS( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  Serial.println("begin setup");


  mqttsetup();
  Serial.println("mqtt setup complete");

  camerasetup();
  Serial.println("camera setup complete");
  
  gpssetup();
  Serial.println("gps setup complete");

  
  // Now set up two tasks to run independently.
  xTaskCreatePinnedToCore(
    TaskBlink
    ,  "TaskBlink"   // A name just for humans
    ,  5000  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TaskMqttSubscribe
    ,  "MqttSubscribe"
    ,  10000  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);


  xTaskCreate(
    TaskGPS
    ,  "GPS"
    ,  5000  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  /*
    Blink
    Turns on an LED on for one second, then off for one second, repeatedly.
      
    If you want to know what pin the on-board LED is connected to on your ESP32 model, check
    the Technical Specs of your board.
  */

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskMqttSubscribe(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    loopmqtt();
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}


void TaskGPS(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;)
  {
    gpsloop();
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}




