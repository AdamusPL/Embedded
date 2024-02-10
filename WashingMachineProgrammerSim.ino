// C++ code
//

#include <LiquidCrystal.h>

int readValue;
int value;
int newValue;

int btnStart;
int btnRinse;
int btnFast;
int btnRPM;
int btnStopSpin;
bool pressedStart = false;
bool pressedRinse = false;
bool pressedFast = false;
bool pressedRPM = false;
bool pressedStopSpin = false;

//array with programme names
String programmes[16]=
{
  "Odpompowanie",
  "Welna 30",
  "Reczne zimna",
  "Delikatne 30",
  "Syntetyki 60",
  "Syntetyki 40",
  "Syntetyki 30",
  "OFF",
	"Bawelna 30",
  "Bawelna 40",
  "Bawelna 60",
  "Intensywne 60",
  "Bawelna 90",
  "Wstepne 60",
  "Plukanie",
  "Wirowanie"
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

//LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(7,6,5,4,3,2);

void setup()
{
  Serial.begin(9600);
  //potentiometer setting programme
  pinMode(A0, INPUT);
  //buttons setting additional options / starting machine
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  //lcd 2x16 initialization
  lcd.begin(16,2);
}

void loop()
{
  btnStart = digitalRead(12);
  btnRinse = digitalRead(11);
  btnFast = digitalRead(10);
  btnRPM = digitalRead(9);
  btnStopSpin = digitalRead(8);
  
  //set cursor at left-up corner
  lcd.home();
  //read programme from potentiometer
  readValue = analogRead(A0);
  //there are 15 programmes (1024/64=16)
  newValue = readValue/64;
  
  //if programme changed
  if(newValue != value){
    //clear lcd
    lcd.clear();
    //assign programme
  	value = newValue;
  }
  
  //print programme with time and options on display
  printProgramme(value);
  
  //Serial.println(value);
}

void printProgramme(int i){
  	//programme name in first row
	lcd.print(programmes[i]);
  
  	//time in second row
    lcd.setCursor(0,2);
    lcd.print(hours[i]);
    lcd.print(":");
  	if(minutes[i]<10){
      lcd.print(0);
  	}
    lcd.print(minutes[i]);
  
  	//options
  	checkIfPressed(btnStart, pressedStart);
  	checkIfPressed(btnRinse, pressedRinse);
  	checkIfPressed(btnFast, pressedFast);
  	checkIfPressed(btnRPM, pressedRPM);
  	checkIfPressed(btnStopSpin, pressedStopSpin);
  
  	int j = 15;
  	lcd.setCursor(j,2);
  	
  	if(pressedStart){
  		timer(value);
  	}
 
  	if(pressedStopSpin){
  		lcd.print("S");
      	j--;
      	lcd.setCursor(j,2);
    }
  
  	if(pressedRPM){
  		lcd.print("6");
      	j--;
      	lcd.setCursor(j,2);
	}
  
  	if(pressedFast){
  		lcd.print("F");
      	j--;
      	lcd.setCursor(j,2);
  	}
  
  	if(pressedRinse){
  		lcd.print("R");
      	j--;
      	lcd.setCursor(j,2);
  	}
  	
}

void checkIfPressed(int& btn, bool& pressed){
  if(btn == 0){
    lcd.clear();
  	pressed = !pressed;
    delay(100);
  }
}

int secs = 60;

void timer(int i){
	delay(1000);
	secs--;
	
  	if (minutes[i] == 0 && hours[i] == 0) {
		pressedStart = false;
      	return;
	}
  	
	if (secs == 0) {
		secs = 60;

		if (minutes[i] == 0) {
			minutes[i] = 59;
			hours[i]--;
		}

		else {
			minutes[i]--;
		}
	}
}