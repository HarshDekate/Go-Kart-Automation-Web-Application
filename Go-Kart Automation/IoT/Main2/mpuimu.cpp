/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>
#include "mqtt.h"
#include "hr.h"


MPU6050 mpu(Wire);

long timer=0;

void mpusetup() {
  //Serial.begin(9600);
  //Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  //mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}



void mpuloop() {
  mpu.update();
  
  
  Serial.println();
	Serial.print("X : ");
	Serial.print(mpu.getAngleX());
	Serial.print("\tY : ");
	Serial.print(mpu.getAngleY());
	Serial.print("\tZ : ");
	Serial.println(mpu.getAccX());
	Serial.println(mpu.getAccY());
	Serial.println(mpu.getAccZ());
  
  if(millis()- timer >2000){
    publishMessage(isFinger(), getBPM(), String(mpu.getAngleX()), String(mpu.getAngleY()), String(mpu.getAngleZ()), String(mpu.getAccX()), String(mpu.getAccY()), String(mpu.getAccZ()));
    timer=millis();
  }
}