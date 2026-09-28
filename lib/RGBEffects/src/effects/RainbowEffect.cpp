#include "RainbowEffect.h"

void RainbowEffect::begin() {
  hue = 0;
}

uint16_t RainbowEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, wheel((uint8_t)((i * 256 / n + hue) & 255)));
  }
  hue += 2;
}

const __FlashStringHelper* RainbowEffect::name() const {
  return F("rainbow");
}

static RainbowEffect s_instance;
IEffect& rainbowEffect = s_instance;