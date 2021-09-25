void zoneControl() {
  if (zoneAuto[zoneNumber]) {
    if (zoneActive[zoneNumber] && (!zonePump[zoneNumber] && !zoneManualPump[zoneNumber])) {
      sensor[zoneNumber] = analogRead(sensPin[zoneNumber]);
      digitalWrite(zoneLED[zoneNumber], HIGH); // Turn Zone Indicator LED On
      digitalWrite(output[zoneNumber], LOW);   
      if ((unsigned long)(millis() - lastSensorReadTime[zoneNumber]) >= sensorReadDelay[zoneNumber]) {
        lastSensorReadTime[zoneNumber] = millis();

        // Set the sensor reading levels for the output trigger for sensor
        if (sensor[zoneNumber] >= triggerLow[zoneNumber]) {
          zonePump[zoneNumber] = true;
          digitalWrite(output[zoneNumber], HIGH);
          lastPumpTimer[zoneNumber] = millis();
          zoneActive[zoneNumber] = false;
        } 
      }
    }    
  }
}
