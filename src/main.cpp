#include <FastLED.h>
#include <Preferences.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <cmath>

#include <SPIFFS.h>   // Include the SPIFFS library

#define NUM_LEDS 83      // 8x8 matrix
#define DATA_PIN 5       // GPIO5
#define BRIGHTNESS 10
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

int r1 = 8;
int r2 = 16;
int r3 = 24;
int r4 = 35;

int pinButtonP = 6;  // GPIO6

// RGB button led
const int pinButtonLedR = 15;  // GPIO15
const int pinButtonLedG = 16;  // GPIO16
const int pinButtonLedB = 17;  // GPIO17
const int channelR = 0;
const int channelG = 1;
const int channelB = 2;
const int frequency = 5000;
const int resolution = 8;

// Menu parameters
int Mode = 1;
// 0 menu, 1 adjust star type, 2 adjust brightness, 3 adjust noise strength
int menuSelection = 1; 

// Button parameters
uint32_t lastButtonPress = 0;
int prevButtonStateP = HIGH;
const uint32_t DEBOUNCE_TIME = 200;  // milliseconds

// Include files
#include "state_manager.hpp"

// State manager instance
StateManager stateManager;

#include "utilities.hpp"
#include "patterns.hpp"
#include "wifisetup.hpp"
#include "serverweb.hpp"

// Display current star type
void displayCurrentStar() {
  int starType = stateManager.getStarType();
  switch (starType) {
    case 0: type_O_star(); break;
    case 1: type_B_star(); break;
    case 2: type_A_star(); break;
    case 3: type_F_star(); break;
    case 4: type_G_star(); break;
    case 5: type_K_star(); break;
    case 6: type_M_star(); break;
    case 7: off_start(); break;
  }
}

void handleButtonPresses() {
  // Short press (< 1s) changes the color temperature
  // Long press (> 1s) increases/decreases noise strength
  static uint32_t buttonPHoldStart = 0;
  uint32_t currentTime = millis();

  // Handle button + (colder stars - decrease index / decrease noise)
  int buttonPState = digitalRead(pinButtonP);
  if (buttonPState == LOW && prevButtonStateP == HIGH) {
    buttonPHoldStart = currentTime;
  } else if (buttonPState == HIGH && prevButtonStateP == LOW) {
    uint32_t holdDuration = currentTime - buttonPHoldStart;
    if (holdDuration < 1000) { // PULSACION CORTA
      if (Mode == 0) {
        // Short press: increase menu selection
        menuSelection++;
        if (menuSelection > 3) menuSelection = 1;  // Wrap around
      } else if (Mode == 1) {
        // Short press: decrease star type
        int newStarType = stateManager.getStarType() + 1;
        if (newStarType > 7) newStarType = 0;  // Wrap around
        stateManager.setStarType(newStarType);
      } else if (Mode == 2) {
        // Short press: increase brightness
        int newBrightness = stateManager.getBrightness() + 10;
        if (newBrightness > 100) newBrightness = 10;  // Wrap around
        stateManager.setBrightness(newBrightness);
        FastLED.setBrightness(newBrightness);
      } else if (Mode == 3) {
        // Short press: Increase noise strength
        int newNoiseStr = stateManager.getNoiseStr() + 25;
        if (newNoiseStr > 75) newNoiseStr = 0;  // Cap noise strength
        stateManager.setNoiseStr(newNoiseStr);
      }
    } else if (holdDuration >= 1000) { // PULSACION LARGA
      if (Mode == 0) {
        // Long press: Enter selected menu
        Mode = menuSelection;
      } else {
        // Long press: Exit to main menu
        Mode = 0;
      }
    }
    buttonPHoldStart = 0;
  }
  prevButtonStateP = buttonPState;
}

void handleButtonLed() {
  // RGB LED to indicate button press
  uint32_t currentTime = millis();

  

  if (Mode == 0) { // In config menu
    // Breathing effect for button LED
    int strength = sin (currentTime / 1000.0 * 3.14) * 127 + 128; // 1-255
    if (menuSelection == 1) {
      // Star type selection - Green
      ledcWrite(channelR, 0);
      ledcWrite(channelG, strength);
      ledcWrite(channelB, 0);
    } else if (menuSelection == 2) {
      // Brightness adjustment - Blue
      ledcWrite(channelR, 0);
      ledcWrite(channelG, 0);
      ledcWrite(channelB, strength);
    } else if (menuSelection == 3) {
      // Noise strength adjustment - Red
      ledcWrite(channelR, strength);
      ledcWrite(channelG, 0);
      ledcWrite(channelB, 0);
    }
  } else if (Mode == 2) {
    // In brightness adjustment mode - Blue solid
    ledcWrite(channelR, 0);
    ledcWrite(channelG, 0);
    ledcWrite(channelB, 200);
  } else if (Mode == 3) {
    // In noise strength adjustment mode - Red solid
    ledcWrite(channelR, 200);
    ledcWrite(channelG, 0);
    ledcWrite(channelB, 0);
  } 
  else {
    // Star mode - off
    ledcWrite(channelR, 0);
    ledcWrite(channelG, 0);
    ledcWrite(channelB, 0);
  }
}


void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  pinMode(pinButtonP, INPUT_PULLUP);

  // Initialize state manager (loads saved state from flash)
  stateManager.begin();

  // Setup RGB button led PWM
  ledcSetup(channelR, frequency, resolution);
  ledcSetup(channelG, frequency, resolution);
  ledcSetup(channelB, frequency, resolution);
  ledcAttachPin(pinButtonLedR, channelR);
  ledcAttachPin(pinButtonLedG, channelG);
  ledcAttachPin(pinButtonLedB, channelB);

  // FastLED setup
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(stateManager.getBrightness());

  // Initial animation: Radial red
  for (int i = 0; i < r1; i++) leds[i] = CRGB::Red;
  FastLED.show();
  delay(250);
  FastLED.clear();
  for (int i = r1; i < r1+r2; i++) leds[i] = CRGB::Red;
  FastLED.show();
  delay(250);
  FastLED.clear();
  for (int i = r1+r2; i < r1+r2+r3; i++) leds[i] = CRGB::Red;
  FastLED.show();
  delay(250);
  FastLED.clear();
  for (int i = r1+r2+r3; i < NUM_LEDS; i++) leds[i] = CRGB::Red;
  FastLED.show();
  delay(250);

  // Setup WiFi Access Point
  setupWiFi();
  setupServer();
}

void loop() {

  // Handle web server
  //server.handleClient();
  
  // Handle button presses to change star type
  handleButtonPresses();
  handleButtonLed();
  
  // Handle deferred state saves (batched to minimize flash wear)
  stateManager.update();
  
  // Display current star type
  displayCurrentStar();
  FastLED.show();
  FastLED.delay(100);  // 50 fps
}