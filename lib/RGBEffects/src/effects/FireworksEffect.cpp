#include "FireworksEffect.h"
#include <Arduino.h>

void FireworksEffect::begin() {
  phase = 0;
  pos = 0;
}

uint16_t FireworksEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void FireworksEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);

  if (phase == 0) {
    for (uint16_t i = 0; i < n; i++) {
      strip.setPixelColor(i, fadeColor(strip.getPixelColor(i), 3));
    }
    if (pos == 0) {
      pos = n - 1;
      center = random(0, n);
    }
    strip.setPixelColor(pos, c);
    if (pos > 0) pos--;
    else {
      phase = 1;
      ring = 0;
    }
  } else {
    int16_t cx = center;
    uint16_t maxRing = (uint16_t)cx;
    uint16_t r2 = (uint16_t)(n - 1 - cx);
    if (r2 > maxRing) maxRing = r2;
    if (maxRing == 0) maxRing = 1;
    for (uint16_t i = 0; i < n; i++) {
      int16_t d = (int16_t)i - cx;
      if (d < 0) d = -d;
      if ((uint16_t)d == ring) {
        uint8_t s = (uint8_t)(255 - (uint32_t)ring * 255 / maxRing);
        strip.setPixelColor(i, scaleColor(c, s));
      } else if ((uint16_t)d < ring) {
        strip.setPixelColor(i, scaleColor(c, 32));
      } else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
    ring++;
    if (ring > maxRing) {
      phase = 0;
      pos = 0;
    }
  }
}

const __FlashStringHelper* FireworksEffect::name() const {
  return F("fireworks");
}

static FireworksEffect s_instance;
IEffect& fireworksEffect = s_instance;