#pragma once

// Buttons initialization
const byte buttonPin = 0;

enum Button {right = 0, left = 405, up = 100, down = 255, select = 640, none = 1023};

const Button button[5] = {right, left, up, down, select};
const byte spread = 50; // this channel width was obtained experimentally
const byte debounceDelay = 10; // this seems to be useless TODO: try to get rid of it
const byte scrollDelay = 100; // you feel free to make it less to speed up scrolling

unsigned long buttonPressedTime;
Button buttonPressed = none;

Button buttonClicked() {
  if (buttonPressed == none) {
    int readValue = analogRead(buttonPin);
    buttonPressedTime = millis(); // updating until hit

    for (int i = 0; i < (sizeof(button) / sizeof(*button)); i++) { // (sizeof(button)/sizeof(*button) = 5
      if (abs(readValue - button[i]) < spread) {
        buttonPressed = button[i];
        return none; // on this stage button was pressed and maybe not released
        // the main thing is that was pressed particually this button
      } // else next button until hit or exit cycle
    }
    // if this code reached, no button was pressed
    return none;
  }
  else { // if button was actually pressed
    if ((millis() - buttonPressedTime) < debounceDelay) { // don't hurry!
      delay(debounceDelay);
      return none;
    }
    else {
      int readValue = analogRead(buttonPin);

      if ( buttonPressed != up && buttonPressed != down && // we want to scroll fast!
           (abs(readValue - buttonPressed) < spread)) {
        buttonPressedTime = millis(); // update for a new debounce delay
        return none;
      }
      else { // debounce delay passed and readValue changed
        if ( buttonPressed == up || buttonPressed == down ) delay(scrollDelay);
        Button result = buttonPressed; // save before cleanup to return it
        buttonPressed = none; // no more pressed
        return result;
      }
    }
  }
  return none; // should be unreachable
}
