#ifndef PINSETUP_H
#define PINSETUP_H

// INPUT: Potentiometer should be connected to 5V and GND
int numPotPin = A1; // Dials number of lights
int colorPotPin = A2; // Potentiometer output connected to analog pin 3
int colorVal = 0; // Variable to store the input from the potentiometer
int numOn = 0;

// OUTPUT: Use digital pins 9-11, the Pulse-width Modulation (PWM) pins
// LED's cathodes should be connected to digital GND
int redPin = 10;   // Red LED,   connected to digital pin 9
int grnPin = 11;  // Green LED, connected to digital pin 10
int bluPin = 12;  // Blue LED,  connected to digital pin 11 

// Program variables
int redVal = 0;
int grnVal = 0;
int bluVal = 0;

#endif
