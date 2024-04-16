 // Define LED pins
const int ledPin1 = D8; 
const int ledPin2 = D5;
const int ledPin3 = D2;

const int buttonPin = D4;            // Push button connected to digital pin 2
int buttonState = HIGH;              // current state of the button
int lastButtonState = HIGH;          // previous state of the button
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int value = 0;  // variable to store the value

const int potPin = A0;  // Potentiometer connected to analog pin A0

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // set the button pin as input with internal pull-up resistor
  Serial.begin(9600);                // initialize serial communication

 // set LED pins as outputs
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

 // Set initial brightness to 0
  analogWrite(ledPin1, 0); 
  analogWrite(ledPin2, 0);
  analogWrite(ledPin3, 0);
}

void loop() {
 buttonRead();  // Read the button state
  int potValue = analogRead(potPin);  // Read the potentiometer value
  Serial.println(potValue);  // Print potentiometer value to serial monitor

  // Set LED brightness based on potentiometer value and selected LED
  analogWrite(ledPin1, value == 0 ? map(potValue, 0, 1023, 0, 255) : 0);
  analogWrite(ledPin2, value == 1 ? map(potValue, 0, 1023, 0, 255) : 0);
  analogWrite(ledPin3, value == 2 ? map(potValue, 0, 1023, 0, 255) : 0);
}

void buttonRead() {
  int reading = digitalRead(buttonPin);  // read the state of the button
  if (reading != lastButtonState) {      // if the button state has changed
    lastDebounceTime = millis();         // reset the debounce timer
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {  // if the button state has been stable
    if (reading != buttonState) {                       // if the button state has changed
      buttonState = reading;                            // update the button state
      if (buttonState == LOW) {                         // if the button is pressed
        value = (value + 1) % 3;                        // increment the value (0 to 2) and loop back to 0 if it reaches 3
        Serial.print("Value: ");
        Serial.println(value);  // print the current value
      }
    }
  }
  lastButtonState = reading;  // save the current state of the button
}
