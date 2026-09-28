#include "RainEffect.h"
#include <Arduino.h>

void RainEffect::begin() {
  uint16_t n = (uint16_t)NUM_LEDS;
  for (uint16_t i = 0; i < n; i++) drop[i] = 0;
}

uint16_t RainEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  if (n > (uint16_t)NUM_LEDS) n = (uint16_t)NUM_LEDS;

  for (uint16_t i = n - 1; i > 0; i--) {
    drop[i] = (uint8_t)(((uint16_t)drop[i - 1] * 7 + 16) >> 3);
  }
  drop[0] = 0;

  uint16_t topRange = n / 4;
  if (topRange == 0) topRange = 1;
  for (uint8_t k = 0; k < 2; k++) {
    if (random(0, 100) < 45) {
      drop[random(0, topRange)] = 255;
    }
  }

  for (uint16_t i = 0; i < n; i++) {
    uint8_t v = drop[i];
    uint8_t tint = (v > 200) ? v : 0;
    strip.setPixelColor(i, tint, tint, v);
  }
}

const __FlashStringHelper* RainEffect::name() const {
  return F("rain");
}

static RainEffect s_instance;
IEffect& rainEffect = s_instance;