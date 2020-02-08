#pragma once

#include "RGBW-led-tuner.h" // all global variables are here

void waveButtonsCheck() {
  switch (buttonClicked()) {
    case right:
    case left: {
        if (waveEntry != waveBack)
          waveEntry = waveBack;
        else
          waveEntry = wavePicker;
        waveMenu.change_screen(waveEntry);
        break;
      }
    case up: {
        waveMenu.call_function(increase);
        break;
      }
    case down: {
        waveMenu.call_function(decrease);
        break;
      }
    case select: {
        if (waveEntry == waveBack) {
          currentMenu = main;
          waveEntry = wavePicker; // clear before exit
          waveMenu.change_screen(waveEntry);
          systemMenu.change_menu(mainMenu);
        }
        else
          waveMenu.switch_focus();
        break;
      }
    case none:
      break;
  }
}
