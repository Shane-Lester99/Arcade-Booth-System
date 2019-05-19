/*
Joystick module

This module is the interface between the ugly Analog data and nice data
that is easy for the rest of the program to use.
*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

class Joystick {
  public:
  // Reads data to console to make sure everything is working properly.
  void readJoystick();
  // This will output nice clean data to the rest of the program so it
  // can use the joystick easily.
  String isDirection();
  
  private:
  
  // No data.
  
};

#endif