#include <string>
#include "LiquidCrystal_I2C.h"

#define POT_READ_INTERVAL 500  // Read potentiometer every 500ms

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousMillis = 0;

const int potentiometerPin = 34;
int potentiometerValue = 0;
int newValue = 7;
int value;

//water drop
byte rinseChar[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000
};

//right arrow
byte fastChar[] = {
  B00000,
  B11000,
  B01100,
  B00110,
  B00011,
  B00110,
  B01100,
  B11000
};

//arrow down
byte RPMChar[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000
};

//snail
byte stopSpinChar[] = {
  B00000,
  B00000,
  B01100,
  B10010,
  B10100,
  B10001,
  B01110,
  B00000
};

//padlock
byte lockChar[] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111
};

const String programmes[16]=
{
  "Drain",
  "Wool 30",
  "Hand-wash cold",
  "Delicates 30",
  "Synthetics 60",
  "Synthetics 40",
  "Synthetics 30",
  "OFF",
	"Cottons 30",
  "Cottons 40",
  "Cottons 60",
  "Intensive 60",
  "Cottons 90",
  "Pre-wash 60",
  "Rinse",
  "Spin"
};

//array with hours of programmes
int hours[16]={
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0
};

//array with minutes of programmes
int minutes[16]={
  1,
  45,
  45,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  20,
  10
};

int btnStart;
int btnRinse;
int btnFast;
int btnRPM;
int btnStopSpin;

const int btnStartPin = 13;
const int btnRinsePin = 14;
const int btnFastPin = 18;
const int btnRPMPin = 19;
const int btnStopSpinPin = 23;

bool btnStartPressed = false;
bool btnRinsePressed = false;
bool btnFastPressed = false;
bool btnRPMPressed = false;
bool btnStopSpinPressed = false;

String functions = "";

void setup() {
  //init display
  lcd.init();
  lcd.backlight();

  //setup tact switches
  pinMode(btnStartPin, INPUT_PULLUP);
  pinMode(btnRinsePin, INPUT_PULLUP);
  pinMode(btnFastPin, INPUT_PULLUP);
  pinMode(btnRPMPin, INPUT_PULLUP);
  pinMode(btnStopSpinPin, INPUT_PULLUP);

  Serial.begin(115200);
  delay(1000);
}

void loop() {
  //check state of tact switches
  btnStart = digitalRead(btnStartPin);
  checkIfButtonIsPressed(btnStart, btnStartPressed);
  btnRinse = digitalRead(btnRinsePin);
  checkIfButtonIsPressed(btnRinse, btnRinsePressed);
  btnFast = digitalRead(btnFastPin);
  checkIfButtonIsPressed(btnFast, btnFastPressed);
  btnRPM = digitalRead(btnRPMPin);
  checkIfButtonIsPressed(btnRPM, btnRPMPressed);
  btnStopSpin = digitalRead(btnStopSpinPin);
  checkIfButtonIsPressed(btnStopSpin, btnStopSpinPressed);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= POT_READ_INTERVAL) {
    previousMillis = currentMillis;
    // programme name, based on potentiometer
    potentiometerValue = analogRead(potentiometerPin);
    value = potentiometerValue / 256;

    if (btnStartPressed){
      //print lock symbol
      lcd.createChar(0, lockChar);
      lcd.setCursor(15, 1);
      lcd.write(0);

      timer(newValue);
    }
    else{
      lcd.setCursor(15, 1);
      lcd.print(" ");
    }

    if (btnRinsePressed){
      lcd.createChar(1, rinseChar);
      lcd.setCursor(11, 1);
      lcd.write(1);
    }
    else{
      lcd.setCursor(11, 1);
      lcd.print(" ");
    }
    if(btnFastPressed){
      lcd.createChar(2, fastChar);
      lcd.setCursor(12, 1);
      lcd.write(2);
    }
    else{
      lcd.setCursor(12, 1);
      lcd.print(" ");
    }
    if (btnRPMPressed){
      lcd.createChar(3, RPMChar);
      lcd.setCursor(13, 1);
      lcd.write(3);
    }
    else{
      lcd.setCursor(13, 1);
      lcd.print(" ");
    }
    if (btnStopSpinPressed){
      lcd.createChar(4, stopSpinChar);
      lcd.setCursor(14, 1);
      lcd.write(4);
    }
    else{
      lcd.setCursor(14, 1);
      lcd.print(" ");
    }

    if (newValue != value){
      newValue = value;
      lcd.clear();
      printProgramme(newValue);
    }
  }  
}

void checkIfButtonIsPressed(int& btn, bool& pressed){
  if (btn == 0){
  	pressed = !pressed;
    delay(20);
  }
}

void printProgramme(int position){
  //programme name printed in first line
  lcd.print(programmes[position]);
  printTime(position);
}

void printTime(int position){
  //time left printed in second line
  lcd.setCursor(0, 1);

  lcd.print(hours[position]);
  lcd.print(":");
  if (minutes[position] < 10){
    lcd.print(0);
  }
  lcd.print(minutes[position]);
}

//count from 60 to 0
int secs = 60;

void timer(int i){
	delay(1000);
	secs--;
	
  //if it's end of programme
  if (minutes[i] == 0 && hours[i] == 0) {
      btnStartPressed = false;
      return;
	}
  
  //each minute
	if (secs == 0) {
		secs = 60;

    //0 minutes left but some hours
		if (minutes[i] == 0) {
			minutes[i] = 59;
			hours[i]--;
		}

    //decrease minute
		else {
			minutes[i]--;
		}

    printTime(i);
	}
}
