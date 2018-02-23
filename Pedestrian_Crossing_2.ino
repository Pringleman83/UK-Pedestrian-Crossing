/*
 * UK Pedestrian Traffic Lights
 * By David Bristoll
 * david.bristoll@gmail.com
 * 22 February 2018
 */

// constants
const int buttonPin = 7;
const int waitPin = 8;
const int redManPin = 9;
const int greenManPin = 10;
const int redPin = 11;
const int amberPin = 12;
const int greenPin = 13;

// system settings

// how long after the button has been pressed before we do something?
const int buttonReactDelay = 5000;

// how long do we keep the amber light on before the red light comes on>
const int amberToRedDelay = 5000;

// how long do we stop traffic for before the green man comes on?
const int redToGreenManDelay = 3000;

// how long does the green man flash for before the red man comes on?
const int greenManFlashBeforeRed = 8000;

// how long do we wait after the red man is on before we start to release traffic?
const int redManToAmberDelay = 3000;

// how long do we stop traffic for in total?
const int redToAmberDelay = 30000;

// how quickly does the amber light flash?
const int amberFlashDelay = 500;

// how quickly does the green man flash?
const int greenManFlashDelay = 500;

// how long do we flash the amber light the green light comes on?
const int amberToGreenDelay = 5000;

// variables
bool buttonPressed = false;
bool amberState = false;
bool redState = false;
bool amberFlashState = false;
bool greenManFlashState = false;
int stage = 10;
unsigned long buttonPreviousMillis = 0;
unsigned long amberPreviousMillis = 0;
unsigned long redPreviousMillis = 0;
unsigned long flashingAmberPreviousMillis = 0;
unsigned long amberFlashPreviousMillis = 0;
unsigned long greenManFlashPreviousMillis = 0;

void setup() {

  // set pin modes
  int inMin = 8; // lowest input pin
  int inMax = 13; // highest input pin
  for(int i=inMin; i<=inMax; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);

  // traffic light default state: green for traffic - red for pedestrians - wait is off.
  digitalWrite(waitPin, LOW);
  digitalWrite(redManPin, HIGH);
  digitalWrite(greenManPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(amberPin, LOW);
  digitalWrite(redPin, LOW);
}

void loop() {

  // get current time running (every cycle)
  unsigned long currentMillis = millis();

  // poll button state (every cycle)
  int buttonVal = digitalRead(buttonPin);
  
  // if button press has been detected during a stage when it can be pressed and it hasn't already been detected
  if (stage > 6 && buttonVal == LOW && buttonPressed == false) {
    digitalWrite(waitPin, HIGH);
    if (buttonPressed == false){
      buttonPreviousMillis = currentMillis;
    }
    buttonPressed = true;
  }

  // if button has been pressed and buttonReactDelay time has passed since it was pressed
  // turn off greenPin - turn on amberPin
  if (buttonPressed == true && currentMillis - buttonPreviousMillis >= buttonReactDelay && stage == 10){
    amberPreviousMillis = currentMillis;
    amberState = true;
    buttonPressed = false;
    digitalWrite(greenPin, LOW);
    digitalWrite(amberPin, HIGH);
  }

  // if amberPin has been on for amberToRedDelay time
  // turn off amberPin - turn on redPin
  if (amberState == true && currentMillis - amberPreviousMillis >= amberToRedDelay){
    redPreviousMillis = currentMillis;
    redState = true;
    amberState = false;
    digitalWrite(amberPin, LOW);
    digitalWrite(redPin, HIGH);
    stage = 5;  
  }

  // if redPin has been on for redToGreenManDelay time
  // turn off redManPin - turn on greenManPin - turn off waitPin
  if (stage == 5 && redState == true && currentMillis - redPreviousMillis >= redToGreenManDelay){
    digitalWrite(redManPin, LOW);
    digitalWrite(greenManPin, HIGH);
    digitalWrite(waitPin, LOW);
    stage = 6;
  }

  // if redPin has been on for redToAmberDelay time - greenManFlashBeforeRed time
  // prepare greenManPin to flash
  if (stage == 6 && redState == true && currentMillis - redPreviousMillis >= redToAmberDelay - greenManFlashBeforeRed){
    greenManFlashPreviousMillis = currentMillis;
    greenManFlashState = true;
    stage = 7;
  }

  // if greenManPin is set to flash and redPin hasn't been on longer than redToAmberDelay time - redManToAmberDelay time
  // if greenManFlashDelay time has passed since last flip - flip greenManPin state (flash)
  if (stage == 7 && greenManFlashState == true && !(currentMillis - redPreviousMillis >= redToAmberDelay - redManToAmberDelay)){
    if (currentMillis - greenManFlashPreviousMillis >= greenManFlashDelay){
      digitalWrite(greenManPin, !digitalRead(greenManPin));
      greenManFlashPreviousMillis = currentMillis;
    }
  }

  // if redPin has been on for redToAmberDelay time - redManToAmberDelay time
  // turn greenManPin off (ensure it is off after flashing) - turn redManPin on
  if (stage == 7 && redState == true && currentMillis - redPreviousMillis >= redToAmberDelay - redManToAmberDelay){
    digitalWrite(greenManPin, LOW);
    digitalWrite(redManPin, HIGH);
  }

  // if redPin has been on for redToAmberDelay time
  // turn off redPin - set amberPin to flash
  if (stage == 7 && redState == true && currentMillis - redPreviousMillis >= redToAmberDelay){
    amberFlashPreviousMillis = currentMillis;
    flashingAmberPreviousMillis = currentMillis;
    digitalWrite(redPin, LOW);
    redState = false;
    greenManFlashState = false;
    amberFlashState = true;
    stage = 8;
  }

  // if amberPin is set to flash
  // if amberFlashDelay time has passed since last flip, flip state of amberPin (flash)
  if (stage == 8 && amberFlashState == true){
   // digitalWrite(redPin, LOW);
    if (currentMillis - flashingAmberPreviousMillis >= amberFlashDelay){
      digitalWrite(amberPin, !digitalRead(amberPin));
      flashingAmberPreviousMillis = currentMillis;
    }
  }

  // if amberPin has been set to flash for amberToGreenDelay time
  // ensure amberPin is off after flashing - turn on greenPin
  // if button has been pressed since greenManPin was set to flash - reset button timer as traffic has only just been released
  
  if (stage == 8 && amberFlashState == true && currentMillis - amberFlashPreviousMillis >= amberToGreenDelay){
    amberFlashState = false;
    digitalWrite(amberPin, LOW);
    digitalWrite(greenPin, HIGH);
    stage = 10;
    if (buttonPressed == true){
      buttonPreviousMillis = currentMillis;
    }  
  }
}

