#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Riston_WIFI";
const char* password = "Garge111";

WebServer server(80);  // Create a web server object on port 80

const int ledPin = 14; 
bool ledState = false; 

void setup() {
  Serial.begin(115200);
   // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, []() {
    // Toggle the LED state on each request
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);

    String txt = ledState ? "LED IS OFF!!!" : "LED IS ON!!!";
    server.send(200, "text/plain", txt);
  });

  server.begin();

  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address of the server
}

void loop() {
  server.handleClient();  // Listen for client requests
}