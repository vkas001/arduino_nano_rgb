#include "RainbowChaseEffect.h"

void RainbowChaseEffect::begin() {
  hue = 0;
  phase = 0;
}

uint16_t RainbowChaseEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowChaseEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  strip.fill(strip.Color(0, 0, 0), 0, n);
  for (uint16_t i = 0; i < n; i++) {
    if ((i + phase) % 3 == 0) {
      strip.setPixelColor(i, wheel((uint8_t)((i * 256 / n + hue) & 255)));
    }
  }
  phase++;
  hue++;
}

const __FlashStringHelper* RainbowChaseEffect::name() const {
  return F("rainbowchase");
}

static RainbowChaseEffect s_instance;
IEffect& rainbowChaseEffect = s_instance;