#include "RipplesEffect.h"
#include <Arduino.h>

void RipplesEffect::begin() {
  for (uint8_t k = 0; k < kRipples; k++) {
    ripple[k].center = 0;
    ripple[k].age = 0;
    ripple[k].active = 0;
  }
}

uint16_t RipplesEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RipplesEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  uint32_t dim = scaleColor(c, 12);
  strip.fill(dim, 0, n);

  uint16_t maxDist = (n > 0) ? n : 1;
  for (uint8_t k = 0; k < kRipples; k++) {
    if (!ripple[k].active) {
      if (random(0, 100) < 20) {
        ripple[k].center = random(0, n);
        ripple[k].age = 0;
        ripple[k].active = 1;
      }
      continue;
    }
    ripple[k].age++;
    uint8_t ring = ripple[k].age;
    if ((uint16_t)ring > maxDist) {
      ripple[k].active = 0;
      continue;
    }
    int16_t s = 255 - (int16_t)ripple[k].age * 12;
    if (s < 0) s = 0;
    int16_t cx = ripple[k].center;
    for (uint16_t i = 0; i < n; i++) {
      int16_t d = (int16_t)i - cx;
      if (d < 0) d = -d;
      if ((uint16_t)d == (uint16_t)ring) {
        strip.setPixelColor(i, scaleColor(c, (uint8_t)s));
      }
    }
  }
}

const __FlashStringHelper* RipplesEffect::name() const {
  return F("ripples");
}

static RipplesEffect s_instance;
IEffect& ripplesEffect = s_instance;