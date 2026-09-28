#include "BeaconEffect.h"

void BeaconEffect::begin() {
  pos = 0;
}

uint16_t BeaconEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void BeaconEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  if (n == 0) return;
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  uint16_t b2 = (uint16_t)(pos + n / 2);
  if (b2 >= n) b2 -= n;
  for (uint16_t i = 0; i < n; i++) {
    uint16_t d1 = (i > pos) ? (uint16_t)(i - pos) : (uint16_t)(pos - i);
    uint16_t d2 = (i > b2) ? (uint16_t)(i - b2) : (uint16_t)(b2 - i);
    uint8_t s1 = (d1 < 3) ? (uint8_t)(96 - d1 * 32) : 0;
    uint8_t s2 = (d2 < 3) ? (uint8_t)(96 - d2 * 32) : 0;
    uint8_t s = (s1 > s2) ? s1 : s2;
    strip.setPixelColor(i, scaleColor(c, s));
  }
  pos++;
  if (pos >= n) pos = 0;
}

const __FlashStringHelper* BeaconEffect::name() const {
  return F("beacon");
}

static BeaconEffect s_instance;
IEffect& beaconEffect = s_instance;