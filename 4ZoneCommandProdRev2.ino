//  --------------------- ZONE COMMAND HV TACO ---------------------
//  ---------------------4 ZONE CONTROL BOARD-------------------
//  ------------------------I2C LCD DISPLAY---------------------
//  --------------------4 USER INPUT BUTTONS--------------------
//  -------------------DESIGNED AND PROGRAMMED BY:--------------
// --------------------------COREY EARL-------------------------
// ----------------REVISION 4.2 (Sept 6th, 2021)----------------
// ----------------All Zones Appear to Function----------------
// ---------------------More Testing Needed--------------------
//----------------Ready for on-site BETA testing---------------

//----------------------------FEATURES:-----------------------------
//-----------------Easy to deactivate/activate each zone------------
//----------------Easy trigger point setting per zone---------------
//-----------User Adjustable and Auto-Adjustable Pump Times---------
//----Also able to Operate Without Sensors on a ~24hr Pump Cycle----

//--------------------------ISSUES:---------------------------------
//-------EEPROM not working right, more testing needed--------

//--------------------------------------------------------

// Libraries
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set I2C Address and display size

// Which zones are active. If a zone is active set as true, if a zone is
// deactived or not needed set to false. Zones are then placed in an array.

bool zoneActive[] = {true,true,true,true};
bool zoneManual[] = {false,false,false,false};
bool zoneAuto[] = {true,true,true,true};
bool zoneAutoTimer[] = {false,false,false,false};
bool zonePump[] = {false,false,false,false};
bool zoneManualPump[] = {false,false,false,false};

// Counters and bools for progressing through each Zone and Manipulating the LCD menu

int zoneNumber = 0; // Which zone the loop is controlling
int menuZone = 0; // Which Zone the menu is viewing/adjusting
int lastMenuZone = 0; 



// Sensor trigger points to trigger each zones output on/off. 

// NOTE: GIKFUN 1.2 Moisture sensors seem to range from ~340(Capacitor submerged
// in water) to ~670(Dry air)
//       GIKFUN 2.0 Seem to run this range (~290 wet, ~700 Dry) but responds
//       much slower as moisture increases, responds quickly to drying). These
//       tests done with factory ~8" jumper harness. Will retest with final
//       length harnesses and adjust MiniTaco V1.0 Soil Sensors seem to run from
//       ~700 - ~930. - 8" Harness, retest with 7.5' Harness MiniTaco V1.5 Soil
//       Sensors seem to run from ~490 - ~890. - 8" Harness, retest with 7.5'
//       Harness

int triggerHigh[] = {550, 550, 550, 550};
int triggerLow[] = {670, 670, 670, 670};

// ---Pin Assignments--

// Set Pin Assignments for User Input Buttons

const int button1 = 10;
const int button2 = 11;
const int button3 = 12;
const int button4 = 13;

// Set Pin Assignments for Zone Status LED's

const int zoneLED[] = {6, 7, 8, 9};  // Zone 1-4 pins for LEDs

// Set pin assignments for OUT pins

const int output[] = {2, 3, 4, 5};  // Zone 1-4 pins for outputs to relays

const int sensPin[] = {A0, A1, A2, A3}; // Zone 1-4 Analog ADC pins

// --Variables--

// Menu Related Variables
bool menuOn = true;   // state of the display menu
int optionSelect = 0; // which menu option is selected
int lastOptionSelect = 0;
int lastItemSelect = 0;
int itemSelect = 0;
int buttonState1 = 0; // current state of each button
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int lastButtonState1 = 0; // previous state of each button
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;
unsigned long displayTimer = 10000; // timer to automatically turn off the display
unsigned long lastDisplayTimer = 0;



// Delay Variables

const int manualDayTimer[] = {86400000, 86400000, 86400000, 86400000}; // delay for once a day manual watering mode
unsigned long lastManualDayTimer[] = {0, 0, 0, 0,};
const int sensorReadDelay[] = {600000, 600000, 600000, 600000}; // delay between sensor readings in millis
unsigned long lastSensorReadTime[] = {0, 0, 0, 0}; // the last time a sensor was read

// Pump timers to monitor zone "on" time of each output. 60000 = 1 minutes

unsigned long pumpTimer[] = {60000, 60000, 60000, 60000}; //Pump timers in array

// Last value of the Pump timers

unsigned long lastPumpTimer[] = {0, 0, 0, 0}; // last value of Pump timers in array

// Analog sensor reading values sensors 1-4

int sensor[] = {0, 0, 0, 0}; // Sensor reading values array


// EEPROM addresses
const int zone1TrigLowAddress = 0;
const int zone2TrigLowAddress = 1;
const int zone3TrigLowAddress = 2;
const int zone4TrigLowAddress = 3;
const int zone1TrigHighAddress = 4;
const int zone2TrigHighAddress = 5;
const int zone3TrigHighAddress = 6;
const int zone4TrigHighAddress = 7;
const int zone1OnAddress = 8;
const int zone2OnAddress = 9;
const int zone3OnAddress = 10;
const int zone4OnAddress = 11;
const int firstBootAddress = 12; // Address to tell the memory if this is the first time this chip has run.
int firstBootCount;


void setup() {
  
//  firstBootCount = EEPROM.read(firstBootAddress);
//  if (firstBootCount == 90) {
//    triggerLow[0] = EEPROM.read(zone1TrigLowAddress);
//    triggerLow[1] = EEPROM.read(zone2TrigLowAddress);
//    triggerLow[2] = EEPROM.read(zone3TrigLowAddress);
//    triggerLow[3] = EEPROM.read(zone4TrigLowAddress);
//    triggerHigh[0] = EEPROM.read(zone1TrigHighAddress);
//    triggerHigh[1] = EEPROM.read(zone2TrigHighAddress);
//    triggerHigh[2] = EEPROM.read(zone3TrigHighAddress);
//    triggerHigh[3] = EEPROM.read(zone4TrigHighAddress);
//    zoneActive[0] = EEPROM.read(zone1OnAddress);
//    zoneActive[1] = EEPROM.read(zone2OnAddress);
//    zoneActive[2] = EEPROM.read(zone3OnAddress);
//    zoneActive[3] = EEPROM.read(zone4OnAddress);
//  }
//  else if (firstBootCount != 90) {
//    EEPROM.write(zone1TrigLowAddress, 800);
//    EEPROM.write(zone2TrigLowAddress, 800);
//    EEPROM.write(zone3TrigLowAddress, 800);
//    EEPROM.write(zone4TrigLowAddress, 800);
//    EEPROM.write(zone1TrigHighAddress, 550);
//    EEPROM.write(zone2TrigHighAddress, 550);
//    EEPROM.write(zone3TrigHighAddress, 550);
//    EEPROM.write(zone4TrigHighAddress, 550);
//    EEPROM.write(zone1OnAddress, true);
//    EEPROM.write(zone2OnAddress, false);
//    EEPROM.write(zone3OnAddress, false);
//    EEPROM.write(zone4OnAddress, false);
//    EEPROM.write(firstBootAddress, 90);
//  }

//  triggerLow[0] = EEPROM.read(zone1TrigLowAddress);
//  triggerLow[1] = EEPROM.read(zone2TrigLowAddress);
//  triggerLow[2] = EEPROM.read(zone3TrigLowAddress);
//  triggerLow[3] = EEPROM.read(zone4TrigLowAddress);
//  triggerHigh[0] = EEPROM.read(zone1TrigHighAddress);
//  triggerHigh[1] = EEPROM.read(zone2TrigHighAddress);
//  triggerHigh[2] = EEPROM.read(zone3TrigHighAddress);
//  triggerHigh[3] = EEPROM.read(zone4TrigHighAddress);
//  zoneActive[0] = EEPROM.read(zone1OnAddress);
//  zoneActive[1] = EEPROM.read(zone2OnAddress);
//  zoneActive[2] = EEPROM.read(zone3OnAddress);
//  zoneActive[3] = EEPROM.read(zone4OnAddress);
  
  lcd.begin();
  lcd.clear();
  lcd.home();
  lcd.print("     --DOROTHY--");
  lcd.setCursor(0, 1);
  lcd.print("     Irrigation");
  lcd.setCursor(0, 2);
  lcd.print("     System 2.0");
  lcd.setCursor(0, 3);
  lcd.print("      LOADING...");
  delay(2000);
  lcd.clear();
  // set LED indicator pins to output.
  pinMode(zoneLED[0], OUTPUT);
  pinMode(zoneLED[1], OUTPUT);
  pinMode(zoneLED[2], OUTPUT);
  pinMode(zoneLED[3], OUTPUT);
  // set OUT pins to output
  pinMode(output[0], OUTPUT);
  pinMode(output[1], OUTPUT);
  pinMode(output[2], OUTPUT);
  pinMode(output[3], OUTPUT);
  // set Sensor pins to input
  pinMode(sensPin[0], INPUT);
  pinMode(sensPin[1], INPUT);
  pinMode(sensPin[2], INPUT);
  pinMode(sensPin[3], INPUT);
  // set Button pins to input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

}

void loop() {
  readButtons();
  zoneLoop();
  displayMenu();
//  settingSave();
}
