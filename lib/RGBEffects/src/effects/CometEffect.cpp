#include "CometEffect.h"

void CometEffect::begin() {
  pos = 0;
  dir = 1;
}

uint16_t CometEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void CometEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, fadeColor(strip.getPixelColor(i), 3));
  }
  pos += dir;
  if (pos >= (int16_t)n - 1) {
    pos = (int16_t)n - 1;
    dir = -1;
  }
  if (pos <= 0) {
    pos = 0;
    dir = 1;
  }
  strip.setPixelColor((uint16_t)pos, c);
  uint16_t trail = (uint16_t)(pos - dir);
  if (trail < n) {
    strip.setPixelColor(trail, scaleColor(c, 150));
  }
}

const __FlashStringHelper* CometEffect::name() const {
  return F("comet");
}

static CometEffect s_instance;
IEffect& cometEffect = s_instance;