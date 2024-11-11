const int flexSensorPin = A0; // Analog pin for flex sensor
const int buzzerPin = D1;     // Digital pin for buzzer (GPIO5)
const int threshold = 316
;    // Threshold value for flex sensor

void setup() {
  Serial.begin(9600);        // Initialize serial communication
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
}

void loop() {
  int flexValue = analogRead(flexSensorPin);
  Serial.print("The bend value:"); // Read the analog value from flex sensor
  Serial.println(flexValue);                 // Print the value to the Serial Monitor

  if (flexValue >= threshold) {
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
  }

  delay(1000); // Wait for 1 second before reading again
}
