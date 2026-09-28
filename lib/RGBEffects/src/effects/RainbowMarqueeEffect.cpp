#include "RainbowMarqueeEffect.h"

void RainbowMarqueeEffect::begin() {
  phase = 0;
}

uint16_t RainbowMarqueeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowMarqueeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  uint16_t bw = n / 10;
  if (bw == 0) bw = 1;
  uint16_t blocks = n / bw;
  if (blocks == 0) blocks = 1;
  for (uint16_t i = 0; i < n; i++) {
    uint16_t bi = i / bw;
    if (((bi + phase) & 1) == 0) {
      strip.setPixelColor(i, wheel((uint8_t)((bi * 256 / blocks) & 255)));
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  phase++;
}

const __FlashStringHelper* RainbowMarqueeEffect::name() const {
  return F("rainbowmarquee");
}

static RainbowMarqueeEffect s_instance;
IEffect& rainbowMarqueeEffect = s_instance;