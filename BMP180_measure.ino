void BMP180_measure () {
  int status;
  double T,P;   
  sprintf(topic,"sensor/%s/pressure",utoa(ESP.getChipId(),chipid,16));  // format the topic
  // BMP180 needs a temperature measurement to perform a pressure reading.
  // Start a temperature measurement: return either number of mS to wait, or 0 if failed
  status = pressure.startTemperature();
  if (status != 0)
    {
    delay(status);  // Wait for the measurement to complete:
    status = pressure.getTemperature(T);  // Retrieve the completed temperature measurement into T: status 0 if failed
    if (status != 0)
      {    
      status = pressure.startPressure(3); // Start a pressure measurement, oversampling rate 3: return either number of mS to wait, or 0 if failed
      if (status != 0)
        {
        delay(status); // Wait for the measurement to complete:
        status = pressure.getPressure(P,T); // Retrieve the completed pressure measurement into P. Need prev T: return 0 if failed
        if (status != 0)
          {
          P = P*100;  //P is in mb, so scale it back to hPa
          dtostrf(P,8,0,pressureString);  // make into a string
          client.publish(topic, pressureString);  
          }
        else client.publish(topic, "error retrieving pressure measurement");
        }
      else client.publish(topic, "error starting pressure measurement");
      }
    else client.publish(topic, "error retrieving temperature measurement");
    }
  else client.publish(topic, "No pressure sensor");  // most likely reason for this failing

}
