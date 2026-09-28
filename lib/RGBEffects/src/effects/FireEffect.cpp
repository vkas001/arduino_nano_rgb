#include "FireEffect.h"
#include <Arduino.h>

void FireEffect::begin() {
  uint16_t n = (uint16_t)NUM_LEDS;
  for (uint16_t i = 0; i < n; i++) heat[i] = 0;
}

uint16_t FireEffect::intervalMs(uint8_t speed) const {
  (void)speed;
  return 40;
}

void FireEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  if (n > (uint16_t)NUM_LEDS) n = (uint16_t)NUM_LEDS;

  for (uint16_t i = 1; i < n; i++) {
    heat[i] = (uint8_t)((((uint16_t)heat[i] * 2) + heat[i - 1]) / 3);
  }

  uint8_t cooldown = 40;
  for (uint16_t i = 1; i < n; i++) {
    uint8_t c = random(0, cooldown);
    heat[i] = (heat[i] > c) ? (uint8_t)(heat[i] - c) : 0;
  }

  for (uint16_t k = 0; k < (uint16_t)(1 + p.speed / 4); k++) {
    heat[random((uint16_t)0, n / 2)] = random(80, 255);
  }

  for (uint16_t i = 0; i < n; i++) {
    uint16_t t = heat[i];
    uint8_t r = (uint8_t)constrain((long)t, 0L, 255L);
    uint8_t g = (uint8_t)constrain((long)(t - 110) * 3, 0L, 255L);
    uint8_t b = (uint8_t)constrain((long)(t - 190) * 4, 0L, 255L);
    strip.setPixelColor(i, r, g, b);
  }
}

const __FlashStringHelper* FireEffect::name() const {
  return F("fire");
}

static FireEffect s_instance;
IEffect& fireEffect = s_instance;