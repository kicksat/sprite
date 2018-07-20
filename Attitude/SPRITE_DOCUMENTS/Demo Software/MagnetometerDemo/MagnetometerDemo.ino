/*
    smeMagnetic Library - Localization Information

    This example print the 3Axis X,Y,Z information

    created 27 May 2015
    by Seve (seve@axelelettronica.it)

    This example is in the public domain
    https://github.com/ameltech

    LSM9DS1  more information available here:
    http://www.stmicroelectronics.com.cn/web/catalog/sense_power/FM89/SC1448/SC1448/PF259998
 */

#include <Arduino.h>
#include <Wire.h>
#include "HardwareSerial.h"

#include <LSM9DS1.h>


// the setup function runs once when you press reset or power the board
void setup() {
    Wire.begin();
    smeMagnetic.begin();
    Serial.begin(9600);
}

void printAxis(int x, int y, int z) {
    Serial.print("  X = ");
    Serial.print(x, DEC);
    Serial.print("     Y = ");
    Serial.print(y, DEC);
    Serial.print("     Z = ");
    Serial.println(z, DEC);
}

// the loop function runs over and over again forever
void loop() {

    int x = 0;
    int y = 0;
    int z = 0;

    x = smeMagnetic.readX();
    y = smeMagnetic.readY();
    z = smeMagnetic.readZ();

    Serial.print("Magnetometer  [mgauss]  :");
    printAxis(x, y, z);

    digitalWrite(LED, LOW);
    delay(100);

    digitalWrite(LED, HIGH);    // turn the LED on
    delay(500);            // wait for a second

}
