#include <FastLED.h>

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

// Star type tracking (0=O hottest to 6=M coldest)
int currentStarType = 0;  // Start at type F (index 3)

// Brigthness control
int brightness = BRIGHTNESS;

// Noise strength (for star twinkling)
int noise_str = 0;

// Button parameters
uint32_t lastButtonPress = 0;
int prevButtonStateP = HIGH;
const uint32_t DEBOUNCE_TIME = 200;  // milliseconds

// Include files
#include "utilities.hpp"
#include "patterns.hpp"

/*******************
 * DIFFERENT STARS AS A FUNCTION OF COLOR TEMPERATURE
 *******************/

// Display current star type
void displayCurrentStar() {
  switch (currentStarType) {
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
        currentStarType++;
        if (currentStarType > 7) currentStarType = 0;  // Wrap around
      } else if (Mode == 2) {
        // Short press: increase brightness
        brightness += 10;
        if (brightness > 100) brightness = 10;  // Wrap around
        FastLED.setBrightness(brightness);
      } else if (Mode == 3) {
        // Short press: Increase noise strength
        noise_str += 25;
        if (noise_str > 75) noise_str = 0;  // Cap noise strength
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
  pinMode(pinButtonP, INPUT_PULLUP);

  // Setup RGB button led PWM
  ledcSetup(channelR, frequency, resolution);
  ledcSetup(channelG, frequency, resolution);
  ledcSetup(channelB, frequency, resolution);
  ledcAttachPin(pinButtonLedR, channelR);
  ledcAttachPin(pinButtonLedG, channelG);
  ledcAttachPin(pinButtonLedB, channelB);

  // FastLED setup
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(5000);
}

void loop() {
  
  // Handle button presses to change star type
  handleButtonPresses();
  handleButtonLed();
  
  // Display current star type
  displayCurrentStar();
  FastLED.show();
  FastLED.delay(100);  // 50 fps
}