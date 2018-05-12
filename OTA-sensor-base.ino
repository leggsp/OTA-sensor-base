//
//This is the base for the OTA sensors
//
#define HOST_NAME "Base OTA code"
#define HOST_PASSWORD "password"   //you might want to change this

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>

//my real wifi credentials are left out of the git repo, look for them first
// you need to copy 'dummy-credentials.h' to 'credentials.h and edit with your local values
#include "credentials.h"
#ifndef CREDENTIALS  //check if they are defined
#include "dummy-credentials.h"
#endif

WiFiClient espClient;  //declare the wifi client
PubSubClient client(espClient);  //declare the mqtt client
  
char buf[20];
char chipid[8];
char topic[24];
long int prev_millis = 0;
long int sample_time = 60000;

void setup() {  
  Serial.begin(9600);
  Serial.print("This is my chipID --> ");
  Serial.println(utoa(ESP.getChipId(),chipid,16));
  setup_wifi();  // connect to wifi
  client.setServer(mqtt_server, 1883);  //MQTT setup
  client.setCallback(callback);

  Wire.begin(12,14);   //set up I2C with SDA,SCL
<
}

 
void loop() { 

  if (!client.connected()) {   // initial connection and subsequent reconnection
    reconnect();
    }
  client.loop();  // process MQTT stuff
  ArduinoOTA.handle();  // process OTA stuff

  // This is the process loop for 'user' code
  if ((millis() - prev_millis) >= sample_time) {  // do this at sample_time intervals
    prev_millis = millis();
    Serial.println(prev_millis);

    
    }
    
  }    // void loop
