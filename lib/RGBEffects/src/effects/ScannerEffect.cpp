#include "ScannerEffect.h"
#include <Arduino.h>

void ScannerEffect::begin() {
  pos = 0;
}

uint16_t ScannerEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void ScannerEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  const float kTwoPi = 6.2831853f;
  for (uint16_t i = 0; i < n; i++) {
    float ang = kTwoPi * ((float)i - (float)pos) / (float)n;
    float v = cosf(ang);
    v = v * v;
    v = v * v;
    uint8_t s = (uint8_t)(v * 255.0f + 0.5f);
    strip.setPixelColor(i, scaleColor(c, s));
  }
  pos++;
  if (pos >= n * 2) pos = 0;
}

const __FlashStringHelper* ScannerEffect::name() const {
  return F("scanner");
}

static ScannerEffect s_instance;
IEffect& scannerEffect = s_instance;