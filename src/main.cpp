#include <Arduino.h>
#include <PWM.h>

static const uint8_t pwmPin = 9; //Pin that goes to fam PWM input (Arduino Uno have a built LED on pin 13)
static const uint32_t frequency = 22000; //PWM frequency in Hz
static const uint8_t errorPin = 13; // Pin to set HIGH if pin PWM frequency is not set successfully

void setup() {
  //Setting up error pin 
  pinMode(errorPin, OUTPUT);
  digitalWrite(errorPin, LOW);

  //Setup PWM pin
  InitTimersSafe();
  bool success = SetPinFrequencySafe(pwmPin, 20000);

  //Check if PWM pin was setup correctly
  if (success) {
    pwmWrite(pwmPin, 64);
  }
  else { //Set errorPin HIGH if it was not

    digitalWrite(10, HIGH);
  }
}

void loop() {

}