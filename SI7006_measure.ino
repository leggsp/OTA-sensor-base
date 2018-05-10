void SI7006_measure() {
 //now do the humidity
 char humidityString[10];
 unsigned int SI7006_data[2];
 
 Wire.requestFrom(SI7006_ADDR,2);  // get 2 bytes
 if(Wire.available() == 2) {
   SI7006_data[0] = Wire.read();
   SI7006_data[1] = Wire.read();
   float humidity = ((SI7006_data[0] * 256.0) + SI7006_data[1]);
   humidity = ((125 * humidity) / 65536.0) - 6;
   dtostrf(humidity,6,2,humidityString);
   sprintf(topic,"sensor/%s/humidity",utoa(ESP.getChipId(),chipid,16));  // format the topic
   client.publish(topic, humidityString);
   }
 else {
   sprintf(topic,"sensor/%s/humidity",utoa(ESP.getChipId(),chipid,16));  // format the topic
   client.publish(topic, "No humidity sensor"); 
   }

 Wire.beginTransmission(SI7006_ADDR);
 Wire.write(0xF5);  //measure humidity
 //Stop I2C transmission
 Wire.endTransmission(SI7006_ADDR);

}
