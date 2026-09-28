#include "SnowEffect.h"
#include <Arduino.h>

void SnowEffect::begin() {
  uint16_t n = (uint16_t)NUM_LEDS;
  for (uint16_t i = 0; i < n; i++) flake[i] = 0;
}

uint16_t SnowEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void SnowEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  if (n > (uint16_t)NUM_LEDS) n = (uint16_t)NUM_LEDS;

  for (uint16_t i = n - 1; i > 0; i--) {
    flake[i] = (uint8_t)(((uint16_t)flake[i - 1] * 6 + 32) >> 3);
  }
  flake[0] = 0;

  if (random(0, 100) < 30) {
    flake[random(0, n / 3 > 0 ? n / 3 : 1)] = (uint8_t)random(120, 256);
  }
  if (random(0, 100) < 20) {
    flake[random(n / 3, n / 2 > n / 3 ? n / 2 : n / 3 + 1)] = (uint8_t)random(120, 256);
  }

  for (uint16_t i = 0; i < n; i++) {
    uint8_t v = flake[i];
    strip.setPixelColor(i, v, v, v);
  }
}

const __FlashStringHelper* SnowEffect::name() const {
  return F("snow");
}

static SnowEffect s_instance;
IEffect& snowEffect = s_instance;