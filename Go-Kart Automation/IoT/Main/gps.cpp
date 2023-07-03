// #include <SoftwareSerial.h>

#include <TinyGPSPlus.h>
#include "mqtt.h"

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPSPlus gps;
// SoftwareSerial ss(13, 12);


float latitude , longitude;

void gpssetup()
{
  //Serial.begin(115200);
  Serial.print("SS Starting");
  Serial2.begin(9600, SERIAL_8N1,16,3);
  Serial.print("SS Started");
}

void gpsloop()
{
  
    while (Serial2.available())
    {  
      //Serial.print("gps available"); 
      if (gps.encode(Serial2.read()))
      {
        //Serial.print("gps read"); 
        if (gps.location.isValid())
        {
        //Serial.print("gps valid");          
          latitude = gps.location.lat();
        // Serial.print("gps latitude %"); 

          //lat_str = String(latitude , 6);
          longitude = gps.location.lng();
          //lng_str = String(longitude , 6);
          Serial.print(latitude);
          Serial.print(",");
          Serial.print(longitude);
          Serial.print("\n");
          publishMessage(String(latitude , 6),String(longitude , 6));
          delay(1000);
        }
      }
      //Serial.print(gps.encode(Serial2.read()));
    }
}