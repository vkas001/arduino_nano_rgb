#include "BounceEffect.h"

void BounceEffect::begin() {
  for (uint8_t k = 0; k < kBalls; k++) {
    x[k] = (uint16_t)((NUM_LEDS - 1) * k / (kBalls - 1));
    dir[k] = (k % 2 == 0) ? 1 : -1;
  }
}

uint16_t BounceEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void BounceEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, fadeColor(strip.getPixelColor(i), 2));
  }
  for (uint8_t k = 0; k < kBalls; k++) {
    x[k] += dir[k];
    if (x[k] <= 0) {
      x[k] = 0;
      dir[k] = 1;
    }
    if (x[k] >= (int16_t)n - 1) {
      x[k] = (int16_t)n - 1;
      dir[k] = -1;
    }
    strip.setPixelColor((uint16_t)x[k], c);
    if (x[k] - 1 >= 0) strip.setPixelColor((uint16_t)(x[k] - 1), scaleColor(c, 96));
    if (x[k] + 1 < (int16_t)n) strip.setPixelColor((uint16_t)(x[k] + 1), scaleColor(c, 96));
  }
}

const __FlashStringHelper* BounceEffect::name() const {
  return F("bounce");
}

static BounceEffect s_instance;
IEffect& bounceEffect = s_instance;