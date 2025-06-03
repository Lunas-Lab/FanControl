#include <Arduino.h>
#include <PWM.h>

static const uint8_t pwmPin = 9;         // Pin that goes to fan PWM input (Arduino Uno have a built LED on pin 13)
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
  bool success = SetPinFrequencySafe(pwmPin, frequency);

  // Blink errorPin if pwmPin was not setup successfully
  if (!success)
  {
    while (true)
    {
      digitalWrite(errorPin, HIGH);
      delay(500);
      digitalWrite(errorPin, LOW);
      delay(500);
    }
  }

  pinMode(adcPin, INPUT);
}

void loop()
{
  //Read the potentiometer value wit the ADC
  //then convert the 10-bit ADC value to 8-bit
  uint8_t adcRead = analogRead(adcPin) >> 2;
  pwmWrite(pwmPin, adcRead);
}