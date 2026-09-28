#include "ChristmasEffect.h"

void ChristmasEffect::begin() {
  phase = 0;
}

uint16_t ChristmasEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void ChristmasEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t green = strip.Color(0, 200, 0);
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, (((i / 2) + phase) & 1) ? red : green);
  }
  phase++;
}

const __FlashStringHelper* ChristmasEffect::name() const {
  return F("christmas");
}

static ChristmasEffect s_instance;
IEffect& christmasEffect = s_instance;