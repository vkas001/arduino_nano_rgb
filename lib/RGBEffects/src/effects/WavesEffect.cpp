#include "WavesEffect.h"

static uint8_t triangle(uint8_t x) {
  return (x < 128) ? (uint8_t)(x * 2) : (uint8_t)(255 - (uint16_t)(x - 128) * 2);
}

void WavesEffect::begin() {
  t = 0;
}

uint16_t WavesEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void WavesEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  t += 32;
  for (uint16_t i = 0; i < n; i++) {
    uint8_t u1 = (uint8_t)(((uint32_t)i * 14 + t * 3) & 0xFF);
    uint8_t u2 = (uint8_t)(((uint32_t)i * 8 + 65535U - t * 2) & 0xFF);
    uint8_t v1 = triangle(u1);
    uint8_t v2 = triangle(u2);
    uint8_t s = (v1 > v2) ? v1 : v2;
    strip.setPixelColor(i, scaleColor(c, s));
  }
}

const __FlashStringHelper* WavesEffect::name() const {
  return F("waves");
}

static WavesEffect s_instance;
IEffect& wavesEffect = s_instance;