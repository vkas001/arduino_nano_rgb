#include "BreathEffect.h"
#include <Arduino.h>

void BreathEffect::begin() {
  phase = 0;
}

uint16_t BreathEffect::intervalMs(uint8_t speed) const {
  (void)speed;
  return 40;
}

void BreathEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  phase += 4;
  if (phase >= 360) phase = 0;
  float wave = (sinf(phase * 3.14159265f / 180.0f) + 1.0f) * 0.5f;
  uint8_t minB = (uint8_t)(p.brightness / 4);
  uint8_t b = (uint8_t)(minB + wave * (float)(p.brightness - minB));
  strip.setBrightness(b);
  strip.fill(strip.Color(p.red, p.green, p.blue), 0, strip.numPixels());
}

const __FlashStringHelper* BreathEffect::name() const {
  return F("breath");
}

static BreathEffect s_instance;
IEffect& breathEffect = s_instance;