#include <LiquidCrystal.h>
#include <LiquidMenu.h>

#include "Button.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Attention! Function numbering starts from 1 (src/LiquidMenu.h:448)
enum FunctionTypes {
  increase = 1,
  decrease = 2,
};

const byte led = 10; // TODO: remove

/// Color-related variables
// menuColor - is current color in menu
enum Colors { red = 1, green = 2, blue = 3, white = 4 } menuColor = 1;
const byte pin[4] = {1, 2, 3, 4}; // TODO: change on real pins!!!
byte level[4] = {0, 0, 0, 0};
byte colorStep = 5; // factor(255) = 1 * 3 * 5 * 17 - These values are best

/// --- MENU DEFINITION --- ///
LiquidLine redTitleLine(6, 0, "RED");
LiquidLine redLevelLine(4, 1, "Level: ", level[red-1]); // about -1 read below
LiquidScreen redScreen(redTitleLine, redLevelLine);

LiquidLine greenTitleLine(6, 0, "GREEN");
LiquidLine greenLevelLine(4, 1, "Level: ", level[green-1]); // about -1 read below
LiquidScreen greenScreen(greenTitleLine, greenLevelLine);

LiquidLine blueTitleLine(6, 0, "BLUE");
LiquidLine blueLevelLine(4, 1, "Level: ", level[blue-1]); // about -1 read below
LiquidScreen blueScreen(blueTitleLine, blueLevelLine);

LiquidLine whiteTitleLine(6, 0, "WHITE");
LiquidLine whiteLevelLine(4, 1, "Level: ", level[white-1]); // about -1 read below
LiquidScreen whiteScreen(whiteTitleLine, whiteLevelLine);

LiquidMenu menu(lcd, redScreen, greenScreen, blueScreen, whiteScreen);
/// END OF MENU DEFINITION ///

// Callback functions
// Attention! realColor equals menuColor-1, because screens start from 1 (src/LiquidMenu.h:805)
void increaseLedLevel() {
  int realColor = menuColor - 1;

  if (level[realColor] < 255)
    level[realColor] += colorStep;
  else
    level[realColor] = 0;

  analogWrite(led, level[realColor]);
}

void decreaseLedLevel() {
  int realColor = menuColor - 1;

  if (level[realColor] > 0)
    level[realColor] -= colorStep;
  else
    level[realColor] = 255;

  analogWrite(led, level[realColor]);
}

// Checks all the buttons.
void buttonsCheck() {
  switch (buttonClicked()) {
    case right: {
        if (menuColor < white)
          menuColor = menuColor + 1;
        else
          menuColor = red;
           menu.change_screen(menuColor);
        break;
      }
    case left: {
        if (menuColor > red)
          menuColor = menuColor - 1;
        else
          menuColor = white;
          menu.change_screen(menuColor);
        break;
      }
    case up: {
        menu.call_function(increase);
        break;
      }
    case down: {
        menu.call_function(decrease);
        break;
      }
    case select: {
        menu.switch_focus();
        break;
      }
    case none:
      break;
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

  menu.update();
}

void loop() {
  buttonsCheck();
  menu.update();
  // dont hurry little arduino!
  delay (30);

}
