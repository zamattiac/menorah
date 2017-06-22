/*
 * Menorah
 * Potentiometers for color and number of days
 * Color options:
 *    white
 *    red, yellow, green, blues, purples
 *    cycle through colors
 * Day options:
 *    1-8
 *    cycle through days
 *    
 *  Matthew Keitelman, 2017
 */
const float pi = 3.14;

int numPotPin = A2; // number pot input pin
int colorPotPin = A1; // color pot input pin
int colorVal = 0; // Input from potentiometer
int fade = 30; // Cycle status
int numOn = 0; // Input from potentiometer
int count = 0; // Cycle status

// OUTPUT: Use digital pins 9-11, the Pulse-width Modulation (PWM) pins
int redPin = 10;   // Red LED,   connected to digital pin 10
int grnPin = 13;  // Green LED, connected to digital pin 13
int bluPin = 12;  // Blue LED,  connected to digital pin 12

// Program variables
int redVal = 0;
int grnVal = 0;
int bluVal = 0;

void setup()
{ 
  pinMode(colorPotPin, INPUT);
  pinMode(numPotPin, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT);

  for (int i = 2; i == 9; i ++) {
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
}

void loop() {
//  Serial.println("Loop");
  numOn = analogRead(numPotPin) / 20;
//  Serial.print("Days: ");
//  Serial.println(numOn);
  decideLights(numOn);
  colorVal = analogRead(colorPotPin);   // read the potentiometer value at the input pin
//  Serial.print("Color val: ");
//  Serial.println(colorVal);
  decideColor(colorVal);
}

void decideLights(int numOn) {
  /*
   * CYCLE - 1-8 - CYCLE
   * Cycles through 1-8 lights on
   */
//   Serial.print("ON: ");
//   Serial.println(numOn);

  if (numOn > 8 || numOn < 1) {
    if (millis() % 5 == 0) count++;
    if (count > 8) count = 0;
    numOn = count;
  }
   
  for (int i = 9; i > 9 - numOn; i --) {
      digitalWrite(i, HIGH);
      delayMicroseconds(1000);
      digitalWrite(i, LOW);
  }
}

void decideColor(int colorVal) {
  /*
   * Sends RGB signals to every LED based on potentiometer reading
   * Three sinusoids 1/3 out of phase for R, G, B
   * FADE - cycles through all colors
   * FADE - white - RGB - white - FADE
   */
   if (colorVal < 10 || colorVal > 1010) {
      fade ++;
      if (fade > 1023) fade = 30;
      colorVal = fade;
   }

  redVal = 127.5*cos(pi/100*colorVal) + 127.5;
  grnVal = 127.5*cos(pi/100*colorVal + 4*pi/3) + 127.5;
  bluVal = 127.5*cos(pi/100*colorVal + 3*pi/3) + 127.5;

  if (colorVal < 23 || colorVal > 1000) {
    redVal = grnVal = bluVal = 255;
  }

  if (colorVal > 1023) {
    redVal = grnVal = bluVal = 255;
  }

  analogWrite(redPin, redVal);   // Write values to LED pins
  analogWrite(grnPin, grnVal); 
  analogWrite(bluPin, bluVal);  
}
