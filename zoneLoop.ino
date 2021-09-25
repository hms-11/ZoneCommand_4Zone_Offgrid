// Loop to progress zoneControl and fault monitor through each zone

void zoneLoop() {
  for (zoneNumber = 0; zoneNumber < 3; zoneNumber++) {
    zoneControl();
    zoneControlManual();
    zoneControlPump();
  }
  for (zoneNumber = 3; zoneNumber > 0; zoneNumber = 0) {
    zoneControl();
    zoneControlManual();
    zoneControlPump();
  }
}