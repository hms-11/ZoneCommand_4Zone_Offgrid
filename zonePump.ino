void zoneControlPump() {    
    if (zonePump[zoneNumber]) {
      if ((unsigned long)(millis() - lastPumpTimer[zoneNumber]) >= pumpTimer[zoneNumber]) {
        if (zoneAutoTimer[zoneNumber]) {
          sensor[zoneNumber] = analogRead(sensPin[zoneNumber]);
          if (sensor[zoneNumber] >= (triggerLow[zoneNumber] - 10)) {
            if (pumpTimer[zoneNumber] <= 360000) {
            pumpTimer[zoneNumber] = pumpTimer[zoneNumber] + 60000;
            }
            else if (pumpTimer[zoneNumber] >= 360000) {
              pumpTimer[zoneNumber] = 360000;
            }  
          }
          else if (sensor[zoneNumber] <= (triggerLow[zoneNumber] + 10)) {
            if (pumpTimer[zoneNumber] > 60000) {
              pumpTimer[zoneNumber] = pumpTimer[zoneNumber] - 60000;
            }
            else if (pumpTimer[zoneNumber] <= 60000) {
              pumpTimer[zoneNumber] = 60000;
            }
          }
        }
        digitalWrite(output[zoneNumber], LOW);
        zoneActive[zoneNumber] = true;
        lastSensorReadTime[zoneNumber] = millis();
        zonePump[zoneNumber] = false;
        zoneManualPump[zoneNumber] = false;
        lastManualDayTimer[zoneNumber] = millis();
      }
    }
    else if (zoneManualPump[zoneNumber]) {
      if ((unsigned long)(millis() - lastPumpTimer[zoneNumber]) >= pumpTimer[zoneNumber]) {
        digitalWrite(output[zoneNumber], LOW);
        zoneActive[zoneNumber] = true;
        zonePump[zoneNumber] = false;
        zoneManualPump[zoneNumber] = false;
        lastManualDayTimer[zoneNumber] = millis();
      }
    }
    else if (!zoneManualPump[zoneNumber] && !zonePump[zoneNumber]) {
      digitalWrite(output[zoneNumber], LOW);
    }
}    