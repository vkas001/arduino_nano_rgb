#include "FlowEffect.h"
#include <Arduino.h>

void FlowEffect::begin() {
  hue = 0;
}

uint16_t FlowEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void FlowEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  float t = (float)hue * 8.0f / 360.0f;
  hue += 2;
  for (uint16_t i = 0; i < n; i++) {
    float fi = (float)i;
    float r = 127.0f + 127.0f * sinf(fi * 0.35f - t);
    float g = 127.0f + 127.0f * sinf(fi * 0.22f + 2.1f - t * 0.9f);
    float b = 127.0f + 127.0f * sinf(fi * 0.14f + 4.2f - t * 0.8f);
    strip.setPixelColor(i, (uint8_t)r, (uint8_t)g, (uint8_t)b);
  }
}

const __FlashStringHelper* FlowEffect::name() const {
  return F("flow");
}

static FlowEffect s_instance;
IEffect& flowEffect = s_instance;