void callback(char* topic, byte* payload, unsigned int length) {
  char pixel_colour, show_type;

  // just echo for now
  client.publish("sensor/echo", (char*)payload);
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  //for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
  //}
  //Serial.println(" ");
  //pixel_colour = payload[1];
  //show_type = payload[0];    
  

}
