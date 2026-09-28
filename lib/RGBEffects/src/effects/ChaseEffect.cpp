#include "ChaseEffect.h"

void ChaseEffect::begin() {
  phase = 0;
}

uint16_t ChaseEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void ChaseEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, ((i + phase) % 3 == 0) ? c : strip.Color(0, 0, 0));
  }
  phase++;
}

const __FlashStringHelper* ChaseEffect::name() const {
  return F("chase");
}

static ChaseEffect s_instance;
IEffect& chaseEffect = s_instance;