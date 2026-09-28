#include "WipeBothEffect.h"

void WipeBothEffect::begin() {
  pos = 0;
}

uint16_t WipeBothEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void WipeBothEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  uint32_t black = strip.Color(0, 0, 0);
  strip.fill(black, 0, n);
  uint16_t half = n / 2;
  uint16_t s;
  if (pos <= half) {
    s = pos;
  } else {
    s = n - pos;
  }
  strip.fill(c, 0, s);
  strip.fill(c, n - s, s);
  pos++;
  if (pos > n) pos = 0;
}

const __FlashStringHelper* WipeBothEffect::name() const {
  return F("wipeboth");
}

static WipeBothEffect s_instance;
IEffect& wipeBothEffect = s_instance;