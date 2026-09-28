#include "NoiseEffect.h"
#include <Arduino.h>

void NoiseEffect::begin() {}

uint16_t NoiseEffect::intervalMs(uint8_t speed) const {
  return fastInterval(speed);
}

void NoiseEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  uint8_t thr = (uint8_t)(8 + p.speed);
  for (uint16_t i = 0; i < n; i++) {
    if (random(0, 100) < thr) {
      strip.setPixelColor(i, scaleColor(c, (uint8_t)random(0, 256)));
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
}

const __FlashStringHelper* NoiseEffect::name() const {
  return F("noise");
}

static NoiseEffect s_instance;
IEffect& noiseEffect = s_instance;