#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>

const char* ssid = "";
const char* password = "";

// WebServer object on port 80
WebServer server(80);

// LED Strip configuration
#define LED_PIN     13      // The pin connected to the DIN of the LED strip
#define NUM_LEDS    30      // Number of LEDs in the strip
#define BRIGHTNESS  64      // Brightness level (0-255)
#define LED_TYPE    WS2812B // Type of LED
#define COLOR_ORDER GRB     // Color order

CRGB leds[NUM_LEDS]; // Array for LED data


// LED state for the strip
bool ledStripOn = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize LED strip
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setCorrection(TypicalLEDStrip); 


  ledStripOn = true;  // Set the default state of the LED strip to "on"
  fill_solid(leds, NUM_LEDS, CRGB::Blue); // Default color set to white
  FastLED.show();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Server IP Address: " + WiFi.localIP().toString());

  // Define web server routes
  server.on("/", HTTP_GET, []() {
    if (ledStripOn) {
      ledStripOn = false;
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn off LED strip
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Turned Off");
    } else {
      ledStripOn = true;
      fill_solid(leds, NUM_LEDS, CRGB::White); // Set default color to blue
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Turned On, try '/red', '/green', '/blue', 'purple', '/yellow', '/colors', '/white';)");
    }
  });

  server.on("/white", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::White);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to White");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

  server.on("/red", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to Red");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

  server.on("/green", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Green);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to Green");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

  server.on("/blue", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Blue);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to Blue");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

   server.on("/purple", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Purple);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to Purple");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

  server.on("/yellow", HTTP_GET, []() {
    if (ledStripOn) {
      fill_solid(leds, NUM_LEDS, CRGB::Yellow);
      FastLED.show();
      server.send(200, "text/plain", "LED Strip Color Set to Yellow");
    } else {
      server.send(200, "text/plain", "LED Strip is Off. Turn it on first.");
    }
  });

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Listen for client requests
  delay(100); // Optional: Add a delay to avoid constant polling
}
