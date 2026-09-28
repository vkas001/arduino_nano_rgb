#include "RainbowWipeEffect.h"

void RainbowWipeEffect::begin() {
  pos = 0;
  hue = 0;
}

uint16_t RainbowWipeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowWipeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  if (pos >= n) pos = 0;
  strip.fill(strip.Color(0, 0, 0), 0, n);
  for (uint16_t i = 0; i < pos; i++) {
    strip.setPixelColor(i, wheel((uint8_t)((i * 256 / n + hue) & 255)));
  }
  pos++;
  hue++;
}

const __FlashStringHelper* RainbowWipeEffect::name() const {
  return F("rainbowwipe");
}

static RainbowWipeEffect s_instance;
IEffect& rainbowWipeEffect = s_instance;