#include "TwinkleEffect.h"
#include <Arduino.h>

void TwinkleEffect::begin() {}

uint16_t TwinkleEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void TwinkleEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, fadeColor(strip.getPixelColor(i), 3));
  }
  uint8_t sparks = (uint8_t)(1 + (p.speed >= 6 ? 1 : 0));
  for (uint8_t k = 0; k < sparks; k++) {
    strip.setPixelColor(random(0, n), random(0, 256), random(0, 256), random(0, 256));
  }
}

const __FlashStringHelper* TwinkleEffect::name() const {
  return F("twinkle");
}

static TwinkleEffect s_instance;
IEffect& twinkleEffect = s_instance;