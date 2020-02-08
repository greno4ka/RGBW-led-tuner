#pragma once

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Attention! Function numbering starts from 1 (src/LiquidMenu.h:448)
enum FunctionTypes {
  increase = 1,
  decrease = 2,
};

const byte led = 10; // TODO: remove

/// Color-related variables
// menuColor - is current color in menu
enum Colors { red = 1, green = 2, blue = 3, white = 4, rgbBack = 5 } menuColor = red;
const byte pin[4] = {1, 2, 3, 4}; // TODO: change on real pins!!!
byte level[4] = {0, 0, 0, 0};
int minWavelength = 400,
    maxWavelength = 760,
    wavelength = minWavelength; // initial value is violet for example
byte colorStep = 5; // factor(255) = 1 * 3 * 5 * 17 - These values are best

enum Menus { main = 1, rgb = 2, wave = 3 } currentMenu = main;

enum MainScreens { rgbScreen = 1, waveScreen = 2 } currentScreen = rgbScreen;

enum Waves { wavePicker = 1, waveBack = 2 } waveEntry = wavePicker;

// Common back line string
LiquidLine backLine(6, 1, "Back");

/// --- RGB MENU DEFINITION --- ///
/// Color picker is just a shown name
LiquidLine rgbTitleLine(2, 0, "COLOR PICKER");

LiquidLine redLevelLine(5, 1, "Red: ", level[red - 1]);
LiquidScreen redScreen(rgbTitleLine, redLevelLine);

LiquidLine greenLevelLine(3, 1, "Green: ", level[green - 1]);
LiquidScreen greenScreen(rgbTitleLine, greenLevelLine);

LiquidLine blueLevelLine(4, 1, "Blue: ", level[blue - 1]);
LiquidScreen blueScreen(rgbTitleLine, blueLevelLine);

LiquidLine whiteLevelLine(3, 1, "White: ", level[white - 1]);
LiquidScreen whiteScreen(rgbTitleLine, whiteLevelLine);

LiquidScreen rgbBackScreen(rgbTitleLine, backLine);

LiquidMenu rgbMenu(lcd, redScreen, greenScreen, blueScreen, whiteScreen);
/// END OF RGB MENU DEFINITION ///

/// --- MAIN MENU DEFINITION --- ///
LiquidLine mainTitleLine(1, 0, "AQUARIUM TUNER");

LiquidLine rgbLine(0, 1, "Color picker");
LiquidScreen rgbMainScreen(mainTitleLine, rgbLine);

LiquidLine waveLine(0, 1, "Color from wave");
LiquidScreen waveMainScreen(mainTitleLine, waveLine);

LiquidMenu mainMenu(lcd, rgbMainScreen, waveMainScreen);

/// --- MENU DEFINITION --- ///
LiquidLine waveTitleLine(0, 0, "COLOR FROM WAVE");
LiquidLine wavelengthLine(0, 1, "Wavelength: ", wavelength);
LiquidScreen wavelengthScreen(waveTitleLine, wavelengthLine);

LiquidScreen waveBackScreen(waveTitleLine, backLine);

LiquidMenu waveMenu(lcd, wavelengthScreen, waveBackScreen);

LiquidSystem systemMenu(mainMenu, rgbMenu, waveMenu);
