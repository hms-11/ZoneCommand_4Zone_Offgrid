void settingSave() {
  EEPROM.update(zone1OnAddress, zoneActive[0]);
  EEPROM.update(zone2OnAddress, zoneActive[1]);
  EEPROM.update(zone3OnAddress, zoneActive[2]);
  EEPROM.update(zone4OnAddress, zoneActive[3]);
  EEPROM.update(zone1TrigLowAddress, triggerLow[0]);
  EEPROM.update(zone2TrigLowAddress, triggerLow[1]);
  EEPROM.update(zone3TrigLowAddress, triggerLow[2]);
  EEPROM.update(zone4TrigLowAddress, triggerLow[3]);
  EEPROM.update(zone1TrigHighAddress, triggerHigh[0]);
  EEPROM.update(zone2TrigHighAddress, triggerHigh[1]);
  EEPROM.update(zone3TrigHighAddress, triggerHigh[2]);
  EEPROM.update(zone4TrigHighAddress, triggerHigh[3]);
}