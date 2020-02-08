#pragma once

#include "RGBW-led-tuner.h" // all global variables are here

#include "wavelengthToRGB.h"

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

void increaseWavelength() {
  if (wavelength < maxWavelength )
    wavelength++;
  else
    wavelength = minWavelength;

  wavelengthToRGB(wavelength, &level[0], &level[1], &level[2]);
  level[3] = 0; // rainbow has now white color
}

void decreaseWavelength() {
  if (wavelength > minWavelength )
    wavelength--;
  else
    wavelength = maxWavelength;

  wavelengthToRGB(wavelength, &level[0], &level[1], &level[2]);
  level[3] = 0; // rainbow has now white color
}
