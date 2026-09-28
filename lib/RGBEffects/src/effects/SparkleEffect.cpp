#include "SparkleEffect.h"
#include <Arduino.h>

void SparkleEffect::begin() {}

uint16_t SparkleEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void SparkleEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  strip.fill(strip.Color(p.red, p.green, p.blue), 0, n);
  uint8_t cnt = (uint8_t)(1 + random(0, 3));
  for (uint8_t k = 0; k < cnt; k++) {
    strip.setPixelColor(random(0, n), strip.Color(255, 255, 255));
  }
}

const __FlashStringHelper* SparkleEffect::name() const {
  return F("sparkle");
}

static SparkleEffect s_instance;
IEffect& sparkleEffect = s_instance;