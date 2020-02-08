#pragma once

#include "RGBW-led-tuner.h" // all global variables are here

void mainButtonsCheck() {
  switch (buttonClicked()) {
    case right: {
        if (currentScreen < waveScreen)
          currentScreen = currentScreen + 1;
        else
          currentScreen = rgbScreen;
        systemMenu.change_screen(currentScreen);
        break;
      }
    case left: {
        if (currentScreen > rgbScreen)
          currentScreen = currentScreen - 1;
        else
          currentScreen = waveScreen;
        systemMenu.change_screen(currentScreen);
        break;
      }
    case select: {
        switch (currentScreen) {
          case rgbScreen: {
              currentScreen = rgbScreen;
              systemMenu.change_screen(currentScreen);
              currentMenu = rgb;
              systemMenu.change_menu(rgbMenu);
              break;
            }
          case waveScreen: {
              currentScreen = rgbScreen;
              systemMenu.change_screen(currentScreen);
              currentMenu = wave;
              systemMenu.change_menu(waveMenu);
              break;
            }
        }
      case up:
      case down:
      case none:
        break;
      }
  }
}
