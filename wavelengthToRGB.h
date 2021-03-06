#pragma once

void wavelengthToRGB(int wavelength, byte *r, byte *g, byte *b) {
  double gamma = 0.80,
         maxIntensity = 255,
         factor,
         red, green, blue;

  if ((wavelength >= 380) && (wavelength < 440)) {
    red = -(wavelength - 440) / (440 - 380);
    green = 0.0;
    blue = 1.0;
  } else if ((wavelength >= 440) && (wavelength < 490)) {
    red = 0.0;
    green = (wavelength - 440) / (490 - 440);
    blue = 1.0;
  } else if ((wavelength >= 490) && (wavelength < 510)) {
    red = 0.0;
    green = 1.0;
    blue = -(wavelength - 510) / (510 - 490);
  } else if ((wavelength >= 510) && (wavelength < 580)) {
    red = (wavelength - 510) / (580 - 510);
    green = 1.0;
    blue = 0.0;
  } else if ((wavelength >= 580) && (wavelength < 645)) {
    red = 1.0;
    green = -(wavelength - 645) / (645 - 580);
    blue = 0.0;
  } else if ((wavelength >= 645) && (wavelength < 781)) {
    red = 1.0;
    green = 0.0;
    blue = 0.0;
  } else {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
  };

  // Let the intensity fall off near the vision limits
  if ((wavelength >= 380) && (wavelength < 420)) {
    factor = 0.3 + 0.7 * (wavelength - 380) / (420 - 380);
  } else if ((wavelength >= 420) && (wavelength < 701)) {
    factor = 1.0;
  } else if ((wavelength >= 701) && (wavelength < 781)) {
    factor = 0.3 + 0.7 * (780 - wavelength) / (780 - 700);
  } else {
    factor = 0.0;
  };

  // Don't want 0^x = 1 for x <> 0
  red = red == 0.0 ? 0 : (byte) round(maxIntensity * pow(red * factor, gamma));
  green = green == 0.0 ? 0 : (byte) round(maxIntensity * pow(green * factor, gamma));
  blue = blue == 0.0 ? 0 : (byte) round(maxIntensity * pow(blue * factor, gamma));

  if ((wavelength < 380) || (wavelength > 781)) {
    red = 255;
    green = 255;
    blue = 255;
  }

  *r = red;
  *g = green;
  *b = blue;
}
