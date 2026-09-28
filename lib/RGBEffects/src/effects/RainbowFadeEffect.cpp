#include "RainbowFadeEffect.h"

void RainbowFadeEffect::begin() {
  hue = 0;
}

uint16_t RainbowFadeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowFadeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, wheel(hue));
  }
  hue++;
}

const __FlashStringHelper* RainbowFadeEffect::name() const {
  return F("rainbowfade");
}

static RainbowFadeEffect s_instance;
IEffect& rainbowFadeEffect = s_instance;