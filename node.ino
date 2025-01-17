#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char* ssid     = "gkmmano";
const char* password = "13gkmmano";

const char* server = "api.thingspeak.com";
String apiKey = "VPJIUIG40BV2JPNQ"; 

WiFiClient  client;

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

void loop()
{
  latbuf=10;
   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            //https://api.thingspeak.com/update?api_key=VPJIUIG40BV2JPNQ&field1=latbuf&field2=lonbuf 
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(latbuf);
                             postStr +="&field2=";
                             postStr += String(lonbuf);
                             //postStr += "\r\n\r\n";
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);

                              Serial.println(latbuf);
                              Serial.println(lonbuf);
                      }
        client.stop();
        delay(1000);
}
