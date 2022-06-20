const byte ledPins[5] = { 2, 3, 4, 5, 6 };
const byte buttonPins[5] = { A1, A2, A3, A4, A5 };

byte buttonStates[5] = { 0, 0, 0, 0, 0 };
byte lastButtonStates[5] = { 0, 0, 0, 0, 0};

byte randSequence[5] = { 0, 0, 0, 0, 0 };
byte buttonInput[5] = { 0, 0, 0, 0, 0 };

const byte sequenceLength = 5;
const int delayBetweenLeds = 1000;

int counter = 0;


void passedLeds() {
  for (const byte pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(50);
  for (const byte pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(50);
}

void failedLeds() {
  digitalWrite(2, HIGH);
  delay(50);
  digitalWrite(2, LOW);
  delay(50);
}



void setup() {
  // put your setup code here, to run once:
    // Sets a random seed
  randomSeed(analogRead(A0));

  // Initializes the led and button pins
  for (const byte pin : ledPins) {
    pinMode(pin, OUTPUT);
  }
  for (const byte pin : buttonPins) {
    pinMode(pin, INPUT);
  }

  // Shows the random sequence
  for (size_t i = 0; i < sequenceLength; ++i) {
    // Picks a random number between 2 and 6
    const byte randLed = random(2, 7);

    // Records the random sequence
    randSequence[i] = randLed - 2;

    // Makes the random led turn on and off
    digitalWrite(randLed, HIGH);
    delay(delayBetweenLeds / 2);
    digitalWrite(randLed, LOW);
    delay(delayBetweenLeds / 2);
  }

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (counter >= 5) {
    // Turns all the leds off
    for (const byte pin : ledPins) {
      digitalWrite(pin, LOW);
    }
    
    // Checks if the button presses are correct
    bool passed = true;
    for (size_t i = 0; i < 5; ++i) {
      if (randSequence[i] != buttonInput[i]) passed = false;
    }

    if (passed) {
      // If they pressed the buttons correctly
      passedLeds();
    } else {
      failedLeds();
    }
    return;
  }

  
  // Loops over all five buttons
  for (size_t i = 0; i < 5; ++i) {
    // Reads the state of the button
    buttonStates[i] = digitalRead(buttonPins[i]);

    // Compares the button state to the previous button state
    if (buttonStates[i] != lastButtonStates[i]) {
      if (buttonStates[i]) {
        // If the state has changed and the button is pressed,
        // we increase the counter by one, record the button
        // and turn the led on
        digitalWrite(ledPins[i], HIGH);
        
        buttonInput[counter] = i;
        counter++;
        Serial.println("On");
      } else {
        // Turn the led off otherwise
        digitalWrite(ledPins[i], LOW);
      }
    }

    // Update the last button state
    lastButtonStates[i] = buttonStates[i];
    delay(20);
  }
}
