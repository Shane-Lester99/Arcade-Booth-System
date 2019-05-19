#include "Arduino.h"
#include "joystick.h"

String Joystick::isDirection() {
  // Reads
  unsigned int num0 = analogRead(A0);
  delay(100);
  unsigned int num1 = analogRead(A1);
  // Test data to see what values are. This is important to keep to make sure potentiometers and wiring
  // is always accurate.
  Serial.print(num1);
  Serial.print(", ");
  Serial.print(num0);
  Serial.print("\n");
  // This interfaces between the potentiometer which has values 0 to 1024. It will return
  // data one whether we go right, left, up, or down.
  String s = "";
  if (num1 >= 100 && num1 <= 900) {
    s += "A: Nuetral";
  }
  else if (num1 < 100) {
    s+= "A: Right"; 
  }
  else if (num1 > 900) {
    s += "A: Left";
  } else {
     s += "A: Nuetral";
  }
  s += ", ";
  if (num0 >= 100 && num0 <= 900) {
    s += "B: Nuetral";
  }
  else if (num0 < 100) {
    s += "B: Up";
  }
  else if (num0 > 900) {
    s += "B: Down";
  } else {
     s += "B: Nuetral";
  }
  return s ;
  
}
void Joystick::readJoystick() {
  // Just reads the data to console to make sure it is consistent with direction.
  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  Serial.print(analogRead(a0));
  Serial.print(", ");
  Serial.print(analogRead(a1));
  Serial.print(". ");
  Serial.print(isDirection());
  Serial.print("\n");
  delay(100);
}
