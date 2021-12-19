/* 
 *  This code is almost a direct copy/paste from Michael Reeves' except for the 
 *  added option of toggling the laser's state
 *  
 *  Data is to be sent to the Arduino in this format:
 *  X100Y67L0
 *  
 *  Possible values:
 *  X: 0 - 180
 *  Y: 0 - 180
 *  L: 0 (ON) or 1 (OFF)
 *  
 *  Pinouts:
 *  
 *  X (rotation) servo sig: D10
 *  y (pitch) servo sig: D11
 *  laser: D13
 *  
 */

#include <Servo.h>

const int servXPin = 10;
const int servYPin = 11;
const int lazPin = 13;

Servo servX;
Servo servY;

String serialData;

void setup() { 
  servX.attach(servXPin);
  servY.attach(servYPin);
  pinMode(lazPin, OUTPUT);
  Serial.begin(9600);  
  Serial.setTimeout(10); 
}

void loop() { 
  
}

void serialEvent() { // actuates motors, laser
  serialData = Serial.readString();
  servX.write(parseDataX(serialData));
  servY.write(parseDataY(serialData));
  if (parseDataLaz(serialData) == 0) {
    digitalWrite(lazPin, HIGH);
  } else {
    digitalWrite(lazPin, LOW);
  }
}

int parseDataX(String data){  //figures out what the x coord is
  data.remove(data.indexOf("Y"));
  data.remove(data.indexOf("X"), 1);
  return data.toInt();
}

int parseDataY(String data){  //figures out what the y coord is
  data.remove(0, data.indexOf("Y") + 1);
  return data.toInt();
}

int parseDataLaz(String data){  //figures out if the laser is triggered or not
  data.remove(0, data.indexOf("L") + 1);
  return data.toInt();
}
