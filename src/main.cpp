#include <Arduino.h>
#include <PWM.h>

static const uint8_t pwmPin = 9;         // Pin that goes to fam PWM input (Arduino Uno have a built LED on pin 13)
static const uint32_t frequency = 22000; // PWM frequency in Hz
static const uint8_t errorPin = 13;      // Pin to blink if pin PWM frequency is not set successfully
static const uint8_t adcPin = A0;        // Pin to read potentiometer from

void setup()
{
  // Setting up error pin
  pinMode(errorPin, OUTPUT);
  digitalWrite(errorPin, LOW);

  // Setup PWM pin
  InitTimersSafe();
  bool success = SetPinFrequencySafe(pwmPin, 20000);

  // Blink errorPin if pwmPin was not setup successfully
  if (!success)
  {
    while (true)
    {
      digitalWrite(10, HIGH);
      delay(500);
      digitalWrite(10, LOW);
      delay(500);
    }
  }

  pinMode(adcPin, INPUT);
}

void loop()
{
  uint8_t adcRead = analogRead(adcPin) >> 2;
  pwmWrite(pwmPin, adcRead);
}