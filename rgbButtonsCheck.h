#pragma once

#include "RGBW-led-tuner.h" // all global variables are here

void rgbButtonsCheck() {
  switch (buttonClicked()) {
    case right: {
        if (menuColor < rgbBack)
          menuColor = menuColor + 1;
        else
          menuColor = red;
        rgbMenu.change_screen(menuColor);
        break;
      }
    case left: {
        if (menuColor > red)
          menuColor = menuColor - 1;
        else
          menuColor = rgbBack;
        rgbMenu.change_screen(menuColor);
        break;
      }
    case up: {
        rgbMenu.call_function(increase);
        break;
      }
    case down: {
        rgbMenu.call_function(decrease);
        break;
      }
    case select: {
        if (menuColor != rgbBack)
          rgbMenu.switch_focus();
        else {
          currentMenu = main;
          menuColor = red; // clear before exit
          rgbMenu.change_screen(menuColor);
          systemMenu.change_menu(mainMenu);
        }
        break;
      }
    case none:
      break;
  }
}
