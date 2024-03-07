#include <avr/io.h>
#define BUZZER PD2
#define LED PD0
#define MAXVOLT 1023
#define CUTOFFVOLT 1000
#define LOOKBACK 5

#include "pitches.h"

int octave4[] = {NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5};
unsigned short int volt_scale[] = {0, 507, 680, 766, CUTOFFVOLT};
int inputs[] = {PC0, PC1, PC2, PC3};
//This is a counter. If it counts up to 8, then we have not pressed anything in the last 8 checks. Turn the buzzer off.
int playing = 0;
int frequency = 0;

void setup() {
  //Set up the serial connection
  //Serial.begin(9600);

  // [Initializing Pins as Inputs/Outputs]

  // PC0-2 is the analog input from resistor ladder
  // PC3 is the digital input from a single pad
  // PC4 is the analog input from the Pitch Control potentiometer
  DDRC &= (0 << PC0) | (0 << PC1) |(0 << PC2) |(0 << PC3);

  // PD0 is the output to power the indication LED
  // PD2 is the PWM output for the buzzer
  DDRD |= (1 << PD0) | (1 << PD2);


  //Begin the POST method
  digitalWrite(LED, 0);

  for (int i = 0; i < 14; i++) {
    tone(BUZZER, octave4[i]);
    delay(100);
  }
  
  noTone(BUZZER);
  digitalWrite(LED, 1);
  //End POST method
}

void loop() {
  //Loop through all 4 pads.
  for (int i = 0; i < 4; i++) {
    int voltage = analogRead(inputs[i]);
    //int pitchShift = analogRead(PITCHCTRL);


    //If nothing is pressed, skip that pin and look at the next pin
      if (voltage > CUTOFFVOLT){
        Serial.print("Nothing Pressed (" + String(voltage) + ")\n");
        if (playing >= LOOKBACK || frequency == 0) {
          noTone(BUZZER);
          digitalWrite(LED, 1);
          playing = 0;
          frequency = 0;
        } else {
          playing++;
          tone(BUZZER, frequency);
        }
      } else {
        digitalWrite(LED, 0);
        Serial.print("Something pressed: ");
        Serial.print("Pad [" + String(i) + "]. Measuring Voltage: " + String(voltage) + "\n");
        frequency = Frequency(i, voltage);
        tone(BUZZER, frequency);
        playing++;
      } 
      
  }
}


unsigned int Frequency(int pad, int voltage) {
  float lowestError = 500.0, error;
  int index = 0;
  int noSonud = 0;
  // For-loop calculates which voltage value in the volt_scale is the closest to the measured voltage value using percent error.
  // Error is calculated by taking the float absolute value of of the ((current pad's voltage - measured voltage) / current pad's voltage)) * 100. Values were type casted to ensure error remains a "double" type value.
  for (int i = 0; i < sizeof(volt_scale)/sizeof(unsigned short int); i++) {
    if (volt_scale[i] > voltage) {
      error = volt_scale[i] - voltage;
    } else {
      error = voltage - volt_scale[i];
    }
    Serial.print("\n Error [" + String(i) + "]-(" + String(volt_scale[i]) + ") = " + String(error) + " \n");
    if (error < lowestError) { // If the current pad's voltage is the closest to the measured voltage, then we save the error value and index.
      lowestError = error;
      index = pad*4 + i;

      if (volt_scale[i] == CUTOFFVOLT) {
        return 0;
      }
      
    }
  }
  //Serial.print("Expected note: " + String(octave4[index]));

  
  // Returns the frequency given by the detected pad +- a percentage of itself.
  // The percentage is defined by calculating the decimal value of the (pitchShift analog reading/MAX_VOLT), and is then multiplied with the current frequency to return an integer value.
  // To ensure that there's no overflow when converting a negative integer value to an unsigned value, we used this if-statement that returns 0 if the integer is negative or if no touch is detected, and returns the integer value if it's positive.
  if (octave4[index] <= 0.0){
    //playing = 0;
    return 0;
  } else {
    playing = 1;
    return octave4[index];
  }
}
