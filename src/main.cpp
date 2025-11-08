#include <Arduino.h>
#include <AccelStepper.h>

#define LED_PIN            13
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN          -1 //PIN 2 is used

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          -1 //PIN 15 is used

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          -1 //PIN 19 is used

//extruder 1
#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

//extruder 2
#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30


#define SDPOWER            -1

//ChipSelect, Hardware SS Pin on Mega, 10 for Arduino Boards, always kept as output
#define SDCS_PIN           53
#define SD_DETECT_PIN 	   -1 //currently not implemented


#define FAN_PIN            9

#define PS_ON_PIN          12	//ATX , awake=LOW, SLEEP=High
#define KILL_PIN           -1

#define HEATER_0_PIN	10  // Extruder Heater
#define HEATER_1_PIN	8

#define TEMP_0_PIN		13   // ANALOG NUMBERING
#define TEMP_1_PIN		14   // ANALOG NUMBERING

// Create AccelStepper objects for X and Y axes
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set pin 13 as output
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW); // Enable X motor
  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW); // Enable Y motor

  // Set max speed and acceleration for steppers
  stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(500);
  stepperY.setMaxSpeed(1000);
  stepperY.setAcceleration(500);

  Serial.begin(9600);
}

void loop() {
  // Example: Move X and Y axes back and forth between 0 and 1000 steps
  static long targetX = 1000;
  static long targetY = 1000;
  static bool forward = true;

  stepperX.moveTo(targetX);
  stepperY.moveTo(targetY);
  stepperX.run();
  stepperY.run();

  if (stepperX.distanceToGo() == 0 && stepperY.distanceToGo() == 0) {
    forward = !forward;
    targetX = forward ? 1000 : 0;
    targetY = forward ? 1000 : 0;
    digitalWrite(LED_PIN, forward ? HIGH : LOW);
  }

  // Every 2 seconds send a message over serial
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis >= 2000) {
    lastMillis = millis();
    Serial.println("Hello from Arduino!");
  }
}