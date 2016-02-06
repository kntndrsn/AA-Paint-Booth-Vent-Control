/*
   Program: Anderson Auto Paint Booth Vent Control System
   Purpose: Automate the exhaust system in the paint booths
   Author: Kent Anderson(KMA)
   Last Modified: 2/6/2016 by KMA
*/

int exhaustTime = 60;

int eastAirSwitchOffTimer = 60;
int westAirSwitchOffTimer = 60;

int eastAirSwitch = 2;
int westAirSwitch = 3;

int eastFanSwitch = 4;
int westFanSwitch = 5;

int eastVentInternal = 8;
int eastVentExternal = 9;

int westVentInternal = 10;
int westVentExternal = 11;

void setup() {

  pinMode(eastVentInternal, OUTPUT);
  pinMode(eastVentExternal, OUTPUT);

  pinMode(westVentInternal, OUTPUT);
  pinMode(westVentExternal, OUTPUT);

}

void loop() {

  check(eastAirSwitch, eastAirSwitchOffTimer, eastVentInternal, eastVentExternal, eastFanSwitch);

  check(westAirSwitch, westAirSwitchOffTimer, westVentInternal, westVentExternal, westFanSwitch);

  delay(1000);

}

void check(int airSwitchPin, int &timer, int internalVentPin, int externalVentPin, int fanSwitchPin) {

  // If the fan is on
  if (digitalRead(fanSwitchPin) == HIGH) {

    // If air is flowing...
    if (digitalRead(airSwitchPin) == HIGH) {

      // Reset timer
      timer = 0;

      Exhaust(internalVentPin, externalVentPin);

    } else {

      // If air is not being sprayed...
      // continue adding to timer counter
      timer += 1;
      
    }

    // If the set amount of time has elapsed with air NOT being sprayed...
    if (timer >= exhaustTime) {

      Recirculate(internalVentPin, externalVentPin);

    }

  } else {

    CloseAll(internalVentPin, externalVentPin);

  }
}

void Recirculate(int internalVentPin, int externalVentPin) {

  // Open INSIDE vent
  digitalWrite(internalVentPin, LOW);

  // Close OUTSIDE vent
  digitalWrite(externalVentPin, HIGH);

}

void Exhaust(int internalVentPin, int externalVentPin) {

  // Close INSIDE vent
  digitalWrite(internalVentPin, HIGH);

  // Open OUTSIDE vent
  digitalWrite(externalVentPin, LOW);

}

void CloseAll(int internalVentPin, int externalVentPin) {

  // Close INSIDE vent
  digitalWrite(internalVentPin, HIGH);

  // Close OUTSIDE vent
  digitalWrite(externalVentPin, HIGH);

}
