#include "CrossfadeEffect.h"
#include <Arduino.h>

void CrossfadeEffect::begin() {
  phase = 0;
}

uint16_t CrossfadeEffect::intervalMs(uint8_t speed) const {
  (void)speed;
  return 40;
}

void CrossfadeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  phase += 2;
  if (phase >= 360) phase = 0;
  float v = (sinf(phase * 3.14159265f / 180.0f) + 1.0f) * 0.5f;
  uint8_t cr = (uint8_t)(255 - p.red);
  uint8_t cg = (uint8_t)(255 - p.green);
  uint8_t cb = (uint8_t)(255 - p.blue);
  uint8_t r = (uint8_t)(p.red + v * ((float)cr - (float)p.red));
  uint8_t g = (uint8_t)(p.green + v * ((float)cg - (float)p.green));
  uint8_t b = (uint8_t)(p.blue + v * ((float)cb - (float)p.blue));
  strip.fill(strip.Color(r, g, b), 0, strip.numPixels());
}

const __FlashStringHelper* CrossfadeEffect::name() const {
  return F("crossfade");
}

static CrossfadeEffect s_instance;
IEffect& crossfadeEffect = s_instance;