/*
  Library for the MMA8452Q
  By: Jim Lindblom and Andrea DeVore
  SparkFun Electronics

  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14587

  This sketch uses the SparkFun_MMA8452Q library to initialize
  the accelerometer and stream calcuated x, y, z, acceleration
  values from it (in g units).

  Hardware hookup:
  Arduino --------------- MMA8452Q Breakout
    3.3V  ---------------     3.3V
    GND   ---------------     GND
  SDA (A4) --\/330 Ohm\/--    SDA
  SCL (A5) --\/330 Ohm\/--    SCL

  The MMA8452Q is a 3.3V max sensor, so you'll need to do some
  level-shifting between the Arduino and the breakout. Series
  resistors on the SDA and SCL lines should do the trick.

  License: This code is public domain, but if you see me
  (or any other SparkFun employee) at the local, and you've
  found our code helpful, please buy us a round (Beerware
  license).

  Distributed as is; no warrenty given.
*/

#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel;                   // create instance of the MMA8452 class

  float avg_x;
  float avg_y;
  float avg_z;

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  int timeStart = millis();
  int counter = 0;
  float x = 0;
  float y = 0;
  float z = 0;
  while (timeStart < 5000) {
    x = x + accel.getCalculatedX();
    y = y + accel.getCalculatedY();
    z = z + accel.getCalculatedZ();
    timeStart = millis();
    counter++;
  }
  Serial.println("Calibration Complete: ");
  avg_x = x/counter;
  avg_y = y/counter;
  avg_z = z/counter;
  Serial.print("X: ");
  Serial.print(avg_x);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(avg_y);
  Serial.print("\t");
  Serial.print("Z: ");
  Serial.print(avg_z);
  Serial.println();
}

void loop() {
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    Serial.print(accel.getCalculatedX()-avg_x, 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedY()-avg_y, 3);
    Serial.print("\t");
    Serial.print(accel.getCalculatedZ()-avg_z, 3);
    Serial.println();
    delay(100);
  
  }
//  if (accel.available()) {
//    if (abs(accel.getCalculatedX()) > 1) {
//        Serial.print("accelerated in X");
//        Serial.println();
//    }
//    if (abs(accel.getCalculatedY()) > 1) {
//       Serial.print("accelerated in Y");
//       Serial.println();
//    }
//    if (abs(accel.getCalculatedZ()) > 1.5) {
//       Serial.print("accelerated in Z");
//       Serial.println();
//    }
//    delay(5);
//
//  }
}
