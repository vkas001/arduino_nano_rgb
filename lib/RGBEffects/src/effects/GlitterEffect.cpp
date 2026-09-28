#include "GlitterEffect.h"
#include <Arduino.h>

void GlitterEffect::begin() {
  for (uint8_t k = 0; k < kSlots; k++) {
    sx[k] = -1;
    sb[k] = 0;
  }
}

uint16_t GlitterEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void GlitterEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t base = strip.Color(p.red, p.green, p.blue);
  uint32_t white = strip.Color(255, 255, 255);
  strip.fill(base, 0, n);

  for (uint8_t k = 0; k < kSlots; k++) {
    if (sx[k] < 0) {
      if (random(0, 100) < 25) {
        sx[k] = random(0, n);
        sb[k] = (uint8_t)random(160, 256);
      }
    } else {
      sb[k] -= sb[k] >> 2;
      if (sb[k] < 16) {
        sx[k] = -1;
        sb[k] = 0;
      } else {
        strip.setPixelColor((uint16_t)sx[k], scaleColor(white, sb[k]));
      }
    }
  }
}

const __FlashStringHelper* GlitterEffect::name() const {
  return F("glitter");
}

static GlitterEffect s_instance;
IEffect& glitterEffect = s_instance;