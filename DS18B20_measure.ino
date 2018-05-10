void DS18B20_measure() {
  sprintf(topic,"sensor/%s/temperature",utoa(ESP.getChipId(),chipid,16));  // format the base topic
  DS18B20.begin();  
  tempC = DS18B20.getTempCByIndex(0);  // publish the first one as sensor/chipid/temperature
  //convert it and publish
  dtostrf(tempC,6,4,temperatureCString);
  client.publish(topic, temperatureCString);
 
  if (DS18B20.getDeviceCount() > 1) {   // if there are others... publish as sensor/chipid/temperature/deviceid
     for (int i=0; i < DS18B20.getDeviceCount(); i++) {
       DS18B20.getAddress(deviceaddress,i);
       String device_id = "";
       for (int j=0; j<8; j++) {
         sprintf(chipid,"%02X", deviceaddress[j]);            
         device_id = device_id + chipid;
         }
       String topic_str = "sensor/";
       topic_str = topic_str + utoa(ESP.getChipId(),chipid,16);
       topic_str = topic_str + "/temperature/";
       topic_str = topic_str + device_id;
       tempC = DS18B20.getTempCByIndex(i);  
       //convert it and publish
       dtostrf(tempC,6,4,temperatureCString);
      
       topic_str.toCharArray(topic_char, topic_str.length()+1);
       Serial.println(topic_char);
       client.publish(topic_char, temperatureCString);
       }
  }   
  
  DS18B20.requestTemperatures();  //get the next one
}
