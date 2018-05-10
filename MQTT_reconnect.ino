void reconnect() {
  char chipid[8], ip_addr[15]; //used for hex values
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    utoa(ESP.getChipId(),chipid,16);
    // Attempt to connect
    if (client.connect(chipid)) {  //make this a unique client name
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("sensor/announce", "sensor powered on");
      utoa(ESP.getChipId(),chipid,16);
      client.publish("sensor/serial", chipid); //hmmm, this seems to clear chipid, so be careful if you need the variable again
      sprintf(ip_addr, "%3d.%3d.%3d.%3d",WiFi.localIP()[0],WiFi.localIP()[1],WiFi.localIP()[2],WiFi.localIP()[3]);
      client.publish("sensor/ip", ip_addr);
      // ... and resubscribe
      char subscription[30];
      strcpy(subscription, "sensor/command/");
      utoa(ESP.getChipId(),chipid,16);
      strcat(subscription, chipid);
      client.subscribe(subscription);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
