#include "WipeEffect.h"

void WipeEffect::begin() {
  pos = 0;
}

uint16_t WipeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void WipeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  if (pos >= n) pos = 0;
  strip.fill(strip.Color(0, 0, 0), 0, n);
  strip.fill(strip.Color(p.red, p.green, p.blue), 0, pos);
  pos++;
}

const __FlashStringHelper* WipeEffect::name() const {
  return F("wipe");
}

static WipeEffect s_instance;
IEffect& wipeEffect = s_instance;