void displayMenu() {
  if (menuOn) {    // if the display is supposed to be on
    lcd.display(); // turn the display on
    lcd.backlight();

    switch (optionSelect) {

    case 0:
        lcd.home();
        lcd.print("  -ZONE ");
        lcd.print(menuZone+1);
        lcd.print(" ");
        if (zoneActive[menuZone] && !zonePump[menuZone]) {
          lcd.print("ACTIVE");
          lcd.print("-");
          lcd.setCursor(0, 1);
          lcd.print("<                  >");
          lcd.setCursor(0, 2);
          lcd.print(" Press DOWN To See/");
          lcd.setCursor(0, 3);
          lcd.print("   Set Details");
        }
        else if (!zoneActive[menuZone] && !zonePump[menuZone] && !zoneManualPump[menuZone]) {
          lcd.print("DISABLED");
          lcd.print("-");
          lcd.setCursor(0, 1);
          lcd.print("<                  >");
          lcd.setCursor(0, 2);
          lcd.print(" Press DOWN To See/");
          lcd.setCursor(0, 3);
          lcd.print("   Set Details");
        }
        else if (zonePump[menuZone] || zoneManualPump[menuZone]) {
          lcd.print("PUMPING");
          lcd.print("-");
          lcd.setCursor(0, 1);
          lcd.print("<                  >");
          lcd.setCursor(0, 2);
          lcd.print(" Press DOWN To See/");
          lcd.setCursor(0, 3);
          lcd.print("   Set Details");
        }
    break;

    case 1:  
        lcd.home();
        lcd.print("  -ZONE ");
        lcd.print(menuZone+1);
        lcd.print(" SETTING-");
        lcd.setCursor(0, 1);
        lcd.print(" Moisture Level: ");
        lcd.print(sensor[menuZone]);
        lcd.setCursor(0, 2);
        lcd.print("  DRY SOIL SETTING");
        lcd.setCursor(0,3);
        lcd.print("<");
        lcd.setCursor(8, 3);
        lcd.print(triggerLow[menuZone]);
        lcd.setCursor(19,3);
        lcd.print(">");
    break;

    case 2:
        lcd.home();
        lcd.print("  -ZONE ");
        lcd.print(menuZone+1);
        lcd.print(" SETTING-");
        lcd.setCursor(0, 1);
        lcd.print("    Pump Timer: ");
        lcd.setCursor(0, 2);
        lcd.print("<       ");
        lcd.print(pumpTimer[menuZone] / 60000);
        lcd.print("       >");
        lcd.setCursor(0,3);
        lcd.print("       Minutes");
    break;

    case 3:
        lcd.home();
        lcd.print("  -ZONE ");
        lcd.print(menuZone+1);
        lcd.print(" SETTING-");
        lcd.setCursor(0, 1);
        lcd.print("   ZONE: ");
        if (zoneAuto[menuZone] && !zonePump[menuZone] && !zoneManualPump[menuZone]) {
          lcd.print("AUTOMATIC");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS < OR > TO:");
          lcd.setCursor(3, 3);
          lcd.print("GO TO MANUAL MODE");
        }
        else if (zoneManual[menuZone] && !zoneManualPump[menuZone] && !zonePump[menuZone]) {
          lcd.print("MANUAL");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS < OR > TO:");
          lcd.setCursor(3, 3);
          lcd.print("GO TO AUTO MODE");
        }
        else if (zoneManualPump[menuZone]) {
          lcd.print("PUMPING");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS < OR > TO:");
          lcd.setCursor(3, 3);
          lcd.print("GO TO AUTO MODE");
        }
        else if (zonePump[menuZone]) {
          lcd.print("PUMPING");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS < OR > TO:");
          lcd.setCursor(3, 3);
          lcd.print("GO TO MANUAL MODE");
        }
    break;    

    case 4:
        lcd.home();
        lcd.print("  -ZONE ");
        lcd.print(menuZone+1);
        lcd.print(" SETTING-");
        lcd.setCursor(0, 1);
        lcd.print("   ZONE: ");
        if (zoneActive[menuZone] && !zonePump[menuZone]) {
          lcd.print("ACTIVE");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS DOWN TO:");
          lcd.setCursor(4, 3);
          lcd.print("DISABLE");
        }
        else if (!zoneActive[menuZone] && !zonePump[menuZone] && !zoneManualPump[menuZone]) {
          lcd.print("DISABLED");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS DOWN TO:");
          lcd.setCursor(4, 3);
          lcd.print("ACTIVATE");
        }
        else if (zonePump[menuZone] || zoneManualPump[menuZone]) {
          lcd.print("PUMPING");
          lcd.setCursor(0, 2);
          lcd.print("   PRESS DOWN TO:");
          lcd.setCursor(4, 3);
          lcd.print("DISABLE");
        }
    break;
}

    if ((unsigned long)(millis() - lastDisplayTimer) >= displayTimer) {
      menuOn = false;
    }
  } else if (!menuOn) { // if the display is supposed to be off
    lcd.noDisplay();    // turn the display off
    lcd.noBacklight();
    optionSelect = 0; // back to front screen
    itemSelect = 0;
    menuZone = 0;
  }
  if ((buttonState1 == 0) && (!menuOn)) {
    menuOn = true;
    lastDisplayTimer = millis();
   // optionSelect = 0; // back to front screen
   // menuZone = 0;
   // itemSelect = 0;
    lastButtonState1 = buttonState1;
  }
}