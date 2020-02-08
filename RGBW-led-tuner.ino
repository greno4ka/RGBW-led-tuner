#include <LiquidCrystal.h>
#include <LiquidMenu.h>

#include "RGBW-led-tuner.h" // all global variables are here

#include "Button.h"
#include "CallbackFunctions.h"

#include "mainButtonsCheck.h"
#include "rgbButtonsCheck.h"
#include "waveButtonsCheck.h"

// Checks all the buttons.
void buttonsCheck() {
  switch (currentMenu) {
    case main: {
        mainButtonsCheck();
        break;
      }
    case rgb: {
        rgbButtonsCheck();
        break;
      }
    case wave: {
        waveButtonsCheck();
        break;
      }
  }
}

void setup() {
  Serial.begin(250000);
  // initialize output pins for different colors
  for (int color = 0; color < 4; color++)
    pinMode(pin[color], OUTPUT);
  pinMode(led, OUTPUT); // TODO: remove
  lcd.begin(16, 2);

  redLevelLine.attach_function(increase, increaseLedLevel);
  redLevelLine.attach_function(decrease, decreaseLedLevel);
  greenLevelLine.attach_function(increase, increaseLedLevel);
  greenLevelLine.attach_function(decrease, decreaseLedLevel);
  blueLevelLine.attach_function(increase, increaseLedLevel);
  blueLevelLine.attach_function(decrease, decreaseLedLevel);
  whiteLevelLine.attach_function(increase, increaseLedLevel);
  whiteLevelLine.attach_function(decrease, decreaseLedLevel);

  wavelengthLine.attach_function(increase, increaseWavelength);
  wavelengthLine.attach_function(decrease, decreaseWavelength);

  rgbMenu.add_screen(rgbBackScreen); // because max screens in constructor is 4

  systemMenu.update();
}

void loop() {
  buttonsCheck();
  systemMenu.update();
  // dont hurry little arduino!
  delay (30);
}
