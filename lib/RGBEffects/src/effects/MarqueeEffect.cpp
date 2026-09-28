#include "MarqueeEffect.h"

void MarqueeEffect::begin() {
  phase = 0;
}

uint16_t MarqueeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void MarqueeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint16_t bw = n / 8;
  if (bw == 0) bw = 1;
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  for (uint16_t i = 0; i < n; i++) {
    if (((i / bw) + phase) & 1) {
      strip.setPixelColor(i, c);
    } else {
      strip.setPixelColor(i, scaleColor(c, 64));
    }
  }
  phase++;
}

const __FlashStringHelper* MarqueeEffect::name() const {
  return F("marquee");
}

static MarqueeEffect s_instance;
IEffect& marqueeEffect = s_instance;