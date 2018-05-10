//
//780 is in the coat cupboard - UFH returns downstairs
//
#define SENSOR_LOCATION "descriptive_name"
#define SENSOR_PASSWORD "chipid for this one"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SFE_BMP180.h>

// network connection credentials
const char* ssid = "xx";
const char* password = "yy";
const char* mqtt_server = "downstairspi.home";

WiFiClient espClient;  //declare the wifi client
PubSubClient client(espClient);  //declare the mqtt client  
SFE_BMP180 pressure;  //declare the pressure sensor interface

#define SI7006_ADDR 0x40
OneWire oneWire(13);
DallasTemperature DS18B20(&oneWire);

char buf[20];
char pressureString[10];
char chipid[8];
boolean pressure_sensor_present;  // use these to note what we've got on board
boolean humidity_sensor_present;
boolean temperature_sensor_present;
char topic[24];
long int prev_millis = 0;
long int sample_time = 60000;

float tempC;
char temperatureCString[10];
char topic_char[50];

DeviceAddress deviceaddress;


void setup() {  
  Serial.begin(9600);
  Serial.println(utoa(ESP.getChipId(),chipid,16));
  setup_wifi();  // connect to wifi
  client.setServer(mqtt_server, 1883);  //MQTT setup
  client.setCallback(callback);

  Wire.begin(12,14);   //set up I2C with SDA,SCL
  // check what equipment we have
  pressure_sensor_present = (pressure.begin());

  DS18B20.begin();
  if (DS18B20.getDeviceCount() > 0) {
    temperature_sensor_present = true;
    DS18B20.requestTemperatures();   // do a first temperature conversion
    }

  //start I2C transmission to contact SI7006
  Wire.beginTransmission(SI7006_ADDR);
  Wire.write(0xF5);  // do a first humidity measurement
  //Stop I2C transmission
  Wire.endTransmission(SI7006_ADDR);

  delay(750);
}

 
void loop() { 

  if (!client.connected()) {   // initial connection and subsequent reconnection
    reconnect();
    }
  client.loop();  // process MQTT stuff
  ArduinoOTA.handle();  // process OTA stuff

  // This is the process loop for 'user' code
  if ((millis() - prev_millis) > sample_time) {  // do this at sample_time intervals
    prev_millis = millis();

    if (DS18B20.getDeviceCount() > 0) DS18B20_measure();
    SI7006_measure();
    BMP180_measure();
       
    }
    
  }    // void loop
