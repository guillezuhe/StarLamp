#include <FastLED.h>

CRGB leds[NUM_LEDS];
uint8_t hue = 0;

void type_O_star() {
  // Blueish star
  // fill_solid(leds, NUM_LEDS, CRGB::Blue);

  CRGB basecolor = CRGB::Blue;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void type_B_star() {
  // Blue-white star
  //fill_solid(leds, NUM_LEDS, CRGB::Cyan);
  CRGB basecolor = CRGB::Cyan;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void type_A_star() {
  // White star
  //fill_solid(leds, NUM_LEDS, CRGB::White);
  CRGB basecolor = CRGB::White;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void type_F_star() {
  // Yellow-white star
  //fill_solid(leds, NUM_LEDS, CRGB(255, 255, 60)); // RGB (255, 255, 200);

  CRGB basecolor = CRGB(255, 255, 60);

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void type_G_star() {
  // Yellow star
  //fill_solid(leds, NUM_LEDS, CRGB::Yellow);

  CRGB basecolor = CRGB::Yellow;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void type_K_star() {
  // Orange star
  //fill_solid(leds, NUM_LEDS, CRGB::DarkOrange); // Orange
  CRGB basecolor = CRGB::DarkOrange;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }

}

void type_M_star() {
  // Red star
  //fill_solid(leds, NUM_LEDS, CRGB::OrangeRed);

  CRGB basecolor = CRGB::OrangeRed;

  // Add random noise
  for (int i = 0; i < NUM_LEDS; i++) {
    // Generate random offset (0 to noise_str*2), then subtract noise_str
    int8_t offset_r = random8(noise_str * 2) - noise_str;
    int8_t offset_g = random8(noise_str * 2) - noise_str;
    int8_t offset_b = random8(noise_str * 2) - noise_str;
    
    // Use qadd8/qsub8 for saturating math (clamps to 0-255)
    if (offset_r >= 0) leds[i].r = qadd8(basecolor.r, offset_r);
    else leds[i].r = qsub8(basecolor.r, -offset_r);
    
    if (offset_g >= 0) leds[i].g = qadd8(basecolor.g, offset_g);
    else leds[i].g = qsub8(basecolor.g, -offset_g);
    
    if (offset_b >= 0) leds[i].b = qadd8(basecolor.b, offset_b);
    else leds[i].b = qsub8(basecolor.b, -offset_b);
  }
}

void off_start() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}



/************************
 * LED ANIMATION PATTERNS
 ************************/



// Animation 1: Rainbow wave
void rainbowWave() {
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  hue++;
}

// Animation 2: Color palette cycling
void paletteCycle() {
  static uint8_t startIndex = 0;
  startIndex++;
  fill_palette(leds, NUM_LEDS, startIndex, 4, RainbowColors_p, 255, LINEARBLEND);
}

// Animation 3: Plasma effect using noise
void plasma() {
  static uint16_t time = 0;
  time++;
  for (uint8_t y = 0; y < MATRIX_HEIGHT; y++) {
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
      uint8_t noise = inoise8(x * 50, y * 50, time);
      leds[XY(x, y)] = CHSV(noise, 255, 255);
    }
  }
}

// Animation 4: Confetti - random colored speckles
void confetti() {
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(hue + random8(64), 200, 255);
  hue++;
}

// Animation 5: Cylon/Knight Rider scanner
void cylon() {
  static uint8_t pos = 0;
  static int8_t dir = 1;
  
  fadeToBlackBy(leds, NUM_LEDS, 20);
  leds[pos] = CHSV(hue, 255, 255);
  
  pos += dir;
  if (pos >= NUM_LEDS - 1 || pos <= 0) dir = -dir;
  hue++;
}

// Animation 6: Breathing effect
void breathing() {
  uint8_t brightness = beatsin8(15, 20, 255);  // 15 BPM, range 20-255
  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, brightness));
  EVERY_N_MILLISECONDS(50) { hue++; }
}

// Animation 7: Fire effect
void fire() {
  static byte heat[NUM_LEDS];
  
  // Cool down
  for (int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8(heat[i], random8(0, 30));
  }
  
  // Heat rises
  for (int i = NUM_LEDS - 1; i >= 2; i--) {
    heat[i] = (heat[i - 1] + heat[i - 2]) / 2;
  }
  
  // Random sparks at bottom
  if (random8() < 120) {
    heat[random8(8)] = qadd8(heat[random8(8)], random8(160, 255));
  }
  
  // Map heat to colors
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = HeatColor(heat[i]);
  }
}