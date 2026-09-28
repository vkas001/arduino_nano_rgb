#include "CopEffect.h"

void CopEffect::begin() {
  phase = 0;
}

uint16_t CopEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void CopEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  uint16_t half = n / 2;
  uint16_t s = (phase > half) ? half : phase;
  strip.fill(strip.Color(0, 0, 0), 0, n);
  for (uint16_t i = 0; i < half; i++) {
    if (i <= s) strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  for (uint16_t i = half; i < n; i++) {
    if ((n - 1 - i) <= s) strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  phase++;
  if (phase > half * 2) phase = 0;
}

const __FlashStringHelper* CopEffect::name() const {
  return F("cop");
}

static CopEffect s_instance;
IEffect& copEffect = s_instance;