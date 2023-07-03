#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#define AWS_IOT_SUBSCRIBE_TOPIC1 "setFlash"
#define AWS_IOT_SUBSCRIBE_TOPIC2 "setHeadlight"
#define AWS_IOT_SUBSCRIBE_TOPIC3 "setBuzzer"
#define AWS_IOT_SUBSCRIBE_TOPIC4 "setExtra1"
#define AWS_IOT_SUBSCRIBE_TOPIC5 "setExtra2"

#define AWS_IOT_PUBLISH_TOPIC_GPS   "getgps"


 
#define flash 4
#define headlight 2
#define buzzer 13
#define extra1 14
#define extra2 15

 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

int r1=0,r2=0,r3=0,r4=0,r5=0;
 
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  /*##################### Flash #####################*/
  if ( strstr(topic, "setFlash") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay1 = doc["status"];
    r1 = Relay1.toInt();
    if(r1==1)
    {
      digitalWrite(flash, LOW);
      Serial.print("Flash is ON");
    }
    else if(r1==0)
    {
      digitalWrite(flash, HIGH);
      Serial.print("Flash is OFF");
    }
  }
 
  /*##################### Headlight #####################*/
  if ( strstr(topic, "setHeadlight") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay2 = doc["status"];
    r2 = Relay2.toInt();
    if(r2==1)
    {
      digitalWrite(headlight, LOW);
      Serial.print("Headlight is ON");
    }
    else if(r2==0)
    {
      digitalWrite(headlight, HIGH);
      Serial.print("Headlight is OFF");
    }
  }
 
  /*##################### Buzzer #####################*/
  if ( strstr(topic, "setBuzzer") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay3 = doc["status"];
    r3 = Relay3.toInt();
    if(r3==1)
    {
      digitalWrite(buzzer, LOW);
      Serial.print("Buzzer is ON");
    }
    else if(r3==0)
    {
      digitalWrite(buzzer, HIGH);
      Serial.print("Buzzer is OFF");
    }
  }
 
  /*##################### Extra1 #####################*/
  if ( strstr(topic, "setExtra1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay4 = doc["status"];
    r4 = Relay4.toInt();
    if(r4==1)
    {
      digitalWrite(extra1, LOW);
      Serial.print("Extra1 is ON");
    }
    else if(r4==0)
    {
      digitalWrite(extra1, HIGH);
      Serial.print("Extra1 is OFF");
    }
  }

  /*##################### Extra2 #####################*/
  if ( strstr(topic, "setExtra2") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay5 = doc["status"];
    r5 = Relay5.toInt();
    if(r5==1)
    {
      digitalWrite(extra2, LOW);
      Serial.print("Extra2 is ON");
    }
    else if(r5==0)
    {
      digitalWrite(extra2, HIGH);
      Serial.print("Extra2 is OFF");
    }
  }
  Serial.println();
}

String ip2Str(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++) {
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}


void publishMessage(String lat, String lng)
{
  Serial.println("Starting Publish");
  StaticJsonDocument<200> doc;
  doc["lat"] = lat;
  doc["lng"] = lng;
  doc["cam"] = String(ip2Str(WiFi.localIP()));
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC_GPS, jsonBuffer);
  //doc.remove();
  Serial.println("Published");

}
 
void mqttsetup()
{
  // Serial.begin(115200);
  
  pinMode (flash, OUTPUT);
  pinMode (headlight, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (extra1, OUTPUT);
  pinMode (extra2, OUTPUT);
 
  digitalWrite(flash, LOW);
  digitalWrite(headlight, HIGH);
  digitalWrite(buzzer, HIGH);
  digitalWrite(extra1, HIGH);
  digitalWrite(extra2, HIGH);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC2);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC3);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC4);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC5);

 
  Serial.println("AWS IoT Connected!");
}
 
// void dangercontrol(){
//   if(bdanger == true){
//     if(bdangerctrl==true){
//       bdangerctrl=false;
//       digitalWrite(danger, LOW);
//     }
//     else if(bdangerctrl==false){
//       bdangerctrl=true;
//       digitalWrite(danger, HIGH);
//     }
//   }
// }


 
void loopmqtt()
{
  //publishMessage();
  client.loop();
  //dangercontrol();
  //Serial.print("publishing");
  
}