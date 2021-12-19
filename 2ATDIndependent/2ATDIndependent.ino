/*  Data is sent to arduino via a joystick. 
 *  Laser functions are controlled by the joystick button
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
 *  joystick:  
 *    - 5v: 5v
 *    - GND: GND
 *    - VRX: A2
 *    - VRY: A5
 *    - SW: D2
 */

#include <Servo.h>

const int servXPin = 10;
const int servYPin = 11;
const int lazPin = 13;
const int jX = A2;
const int jY = A5;
const int button = 2;

Servo servX;
Servo servY;

int lazState;
int jXState;
int jYState;

void setup() {
  servX.attach(servXPin);
  servY.attach(servYPin);
  pinMode(lazPin, OUTPUT);
  pinMode(jX, INPUT);
  pinMode(jY, INPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  Serial.begin(9600);
}

void loop() {
  lazState = digitalRead(button);  // Toggles laser
  if (lazState == 1) {
    lazState = 0;
  } else {
    lazState = 1;
  }
  digitalWrite(lazPin, lazState);
  
  jXState = analogRead(A2);
  jXState = jXState / 5.68; //scales down to 180 degrees
  servX.write(jXState);

  jYState = analogRead(A5);
  jYState = jYState / 5.68; //scales down to 180 degrees
  servY.write(jYState);

  Serial.print(jXState); // Some debug data sent to the serial monitor
  Serial.print("X");
  Serial.print("\t");
  Serial.print(jYState);
  Serial.print("Y");
  Serial.print("\t");
  Serial.print(lazState);
  Serial.println();
}
