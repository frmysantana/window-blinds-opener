/*
 * Rotates stepper 8 revlutions forward at 6 AM.
 * 
 *
 * The circuit:
 * - Stepper driver powered with 5v, GND
 * - D8-D11 connected to IN1-IN4 on the stepper driver
 *
 * 
 */

#include <Stepper.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
int stepIN1Pin = 8;
int stepIN2Pin = 9;
int stepIN3Pin = 10;
int stepIN4Pin = 11;

int stepsPerRevolution = 2048;

Stepper myStepper(stepsPerRevolution,
                  stepIN1Pin, stepIN3Pin,
                  stepIN2Pin, stepIN4Pin);

void setup()
{
    // set the RPM
    myStepper.setSpeed(19); // max is 19
    Serial.begin(9600);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    // Uncomment to set RTC time (Only do this once)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
}

void loop()
{
    // step one revolution in one direction
    // will need 8 revolutions to open blinds
    
    DateTime now = rtc.now();

    if (now.hour() == 6 && now.minute() == 0 && !now.isPM()) {
      myStepper.step(stepsPerRevolution * 8);
    }

    // somehow activate this with a button...
    if () {
      myStepper.step(-stepsPerRevolution * 8);
    }
}
