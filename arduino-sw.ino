#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Galaxy A33 5G";
const char* password = "krishna priya";

// Replace with your web application's endpoint URL
const char* serverUrl = "https://127.0.0.1:5501"; // Use actual server IP address
const int flexPin = A0;  // Flex sensor connected to A0
const int buzzerPin = D1;  // Buzzer connected to D5

void setup() {
  Serial.begin(9600);
  pinMode(flexPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  int flexValue = analogRead(flexPin);
  Serial.print("Flex Value: ");
  Serial.println(flexValue);

  // Buzzer logic
  if (flexValue > 296) { // Adjust threshold as needed
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Send data to the server
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    if (http.begin(client, serverUrl)) {
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Create the data string to send
      String httpRequestData = "flexValue=" + String(flexValue);
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("Failed to connect to server URL.");
    }
  } else {
    Serial.println("Wi-Fi not connected.");
  }

  delay(1000); // Adjust the delay as needed
}