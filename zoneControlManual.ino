void zoneControlManual() {
  if (zoneManual[zoneNumber]) {
    if (zoneActive[zoneNumber] && (!zonePump[zoneNumber] && !zoneManualPump[zoneNumber])) {
      digitalWrite(zoneLED[zoneNumber], HIGH); // Turn Zone Indicator LED On  
      digitalWrite(output[zoneNumber], LOW);
      sensor[zoneNumber] = 0;
      if ((unsigned long)(millis() - lastManualDayTimer[zoneNumber]) > manualDayTimer[zoneNumber]) {
          zoneManualPump[zoneNumber] = true;
          digitalWrite(output[zoneNumber], HIGH);
          lastPumpTimer[zoneNumber] = millis();
          lastManualDayTimer[zoneNumber] = millis();
          zoneActive[zoneNumber] = false;
      }
    }
  }
}