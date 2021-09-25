void readButtons() {
  buttonState1 = (digitalRead(button1));
  buttonState2 = (digitalRead(button2));
  buttonState3 = (digitalRead(button3));
  buttonState4 = (digitalRead(button4));
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == LOW) { // if the DOWN button has been pressed
      lcd.clear();
      lastDisplayTimer = millis();
      if (optionSelect < 4) { // if we are in the settings change and not passed the last screen.
        optionSelect++;
      } 
      else if (optionSelect = 4) {
        if (zoneActive[menuZone]) {
          zonePump[menuZone] = false;
          zoneManualPump[menuZone] = false;
          zoneActive[menuZone] = false;
          digitalWrite(output[menuZone], LOW);
          digitalWrite(zoneLED[menuZone], LOW); // Turn Zone Indicator LED Off
        }
        else if (zonePump[menuZone]) {
          zonePump[menuZone] = false;
          zoneManualPump[menuZone] = false;
          zoneActive[menuZone] = false;
          digitalWrite(output[menuZone], LOW);
          digitalWrite(zoneLED[menuZone], LOW); // Turn Zone Indicator LED Off
        }
        else if (zoneManualPump[menuZone]) {
          zonePump[menuZone] = false;
          zoneManualPump[menuZone] = false;
          zoneActive[menuZone] = false;
          digitalWrite(output[menuZone], LOW);
          digitalWrite(zoneLED[menuZone], LOW); // Turn Zone Indicator LED Off
        }
        else if (!zoneActive[menuZone]) {
          zonePump[menuZone] = false;
          zoneManualPump[menuZone] = false;
          zoneActive[menuZone] = true;
          lastPumpTimer[menuZone] = millis();
          lastManualDayTimer[menuZone] = millis();
          digitalWrite(zoneLED[menuZone], HIGH);
        }
        optionSelect = 0;
      }
    }
    lastButtonState1 = buttonState1;
  }
  if (buttonState4 != lastButtonState4) {
    if (buttonState4 == LOW) { // if the UP button has been pressed
      lcd.clear();
      lastDisplayTimer = millis();
      if ((optionSelect != 0) && (optionSelect != 0)) { // if we are not in the settings change and not passed the first screen.
        optionSelect--;
      }
    }
    lastButtonState4 = buttonState4;
  }

  if (optionSelect == 0) { // if we are not adjusting settings

    if (buttonState2 != lastButtonState2) {      // if the right button has been pressed
      if (buttonState2 == LOW) { // if the right button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if ((menuZone <= 3) && (menuZone != 3)) { // if we are not past the last menu screen
          menuZone++;
        } 
        else if (menuZone == 3) { // if we are at the last menu screen
          menuZone = 0;
        }
      }
      lastButtonState2 = buttonState2;
    }
    if (buttonState3 != lastButtonState3) {      // if the left button has been pressed
      if (buttonState3 == LOW) { // if the left button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (menuZone > 0) { // if we are not at the first menu screen
          menuZone--;
        } 
        else if (menuZone == 0) {
          menuZone = 3;
        }
      }
      lastButtonState3 = buttonState3;
    }
  }

  else if (optionSelect == 1) { // if we are adjusting settings
    buttonState2 = (digitalRead(button2));
    buttonState3 = (digitalRead(button3));

    if (buttonState2 != lastButtonState2) {      // if the right button has been pressed
      if (buttonState2 == LOW) { // if the right button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (triggerLow[menuZone] < 700) {
          triggerLow[menuZone] = (triggerLow[menuZone] + 10);
        }
        else if (triggerLow[menuZone] >= 700) {
          triggerLow[menuZone] = 700;
        }  
      }
      lastButtonState2 = buttonState2;
    }
    if (buttonState3 != lastButtonState3) {      // if the left button has been pressed
      if (buttonState3 == LOW) { // if the left button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (triggerLow[menuZone] > 600) {
          triggerLow[menuZone] = (triggerLow[menuZone] - 10);
        }
        else if (triggerLow[menuZone] <= 600) {
          triggerLow[menuZone] = 600;
        }
      }
      lastButtonState3 = buttonState3;
    }
  }
   
   else if (optionSelect == 2) { // if we are adjusting settings
    buttonState2 = (digitalRead(button2));
    buttonState3 = (digitalRead(button3));

    if (buttonState2 != lastButtonState2) {      // if the right button has been pressed
      if (buttonState2 == LOW) { // if the right button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (pumpTimer[menuZone] < 600000) {
          pumpTimer[menuZone] = (pumpTimer[menuZone] + 60000);
        }
        else if (pumpTimer[menuZone] >= 600000) {
          pumpTimer[menuZone] = 600000;
        }
      }
      lastButtonState2 = buttonState2;
    }
    if (buttonState3 != lastButtonState3) {      // if the left button has been pressed
      if (buttonState3 == LOW) { // if the left button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (pumpTimer[menuZone] > 60000) {
          pumpTimer[menuZone] = (pumpTimer[menuZone] - 60000);
        }
        else if (pumpTimer[menuZone] <= 60000) {
          pumpTimer[menuZone] = 60000; 
        }
      }
      lastButtonState3 = buttonState3;
    }
   }
   
   else if (optionSelect == 3) { // if we are adjusting settings
    buttonState2 = (digitalRead(button2));
    buttonState3 = (digitalRead(button3));

    if (buttonState2 != lastButtonState2 || buttonState3 != lastButtonState3) {      // if the right button has been pressed
      if (buttonState2 == LOW || buttonState3 == LOW) { // if either button has been pressed
        lcd.clear();
        lastDisplayTimer = millis();
        if (zoneAuto[menuZone] && !zonePump[menuZone] && !zoneManualPump[menuZone]) {
          zoneAuto[menuZone] = false;
          lastManualDayTimer[menuZone] = millis();
          zoneManual[menuZone] = true;
        }
        else if (zoneManual[menuZone] && !zoneManualPump[menuZone] && !zonePump[menuZone]) {
          zoneManual[menuZone] = false;
          zoneAuto[menuZone] = true;
        }
        else if (zoneManualPump[menuZone]) {
          zoneManualPump[menuZone] = false;
          zonePump[menuZone] = true;
          lastManualDayTimer[menuZone] = millis();
          zoneManual[menuZone] = false;
          zoneAuto[menuZone] = true;
        }
        else if (zonePump[menuZone]) {
          lastManualDayTimer[menuZone] = millis();
          zonePump[menuZone] = false;
          zoneManualPump[menuZone] = true;
          zoneAuto[menuZone] = false;
          lastManualDayTimer[menuZone] = millis();
          zoneManual[menuZone] = true;
        }
      }
      lastButtonState2 = buttonState2;
      lastButtonState3 = buttonState3;
    }
   }   
}