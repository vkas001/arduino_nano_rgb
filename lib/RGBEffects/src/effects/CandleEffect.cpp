#include "CandleEffect.h"
#include <Arduino.h>

void CandleEffect::begin() {
  value = (uint8_t)random(120, 201);
}

uint16_t CandleEffect::intervalMs(uint8_t speed) const {
  (void)speed;
  return 80;
}

void CandleEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t target = random(60, 256);
  if (random(0, 100) < 30) {
    value = (uint8_t)target;
  } else if (value < target) {
    value++;
  } else if (value > target) {
    value--;
  }
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  strip.fill(scaleColor(c, value), 0, strip.numPixels());
}

const __FlashStringHelper* CandleEffect::name() const {
  return F("candle");
}

static CandleEffect s_instance;
IEffect& candleEffect = s_instance;