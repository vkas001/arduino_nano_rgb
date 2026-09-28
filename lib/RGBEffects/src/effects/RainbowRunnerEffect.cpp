#include "RainbowRunnerEffect.h"

void RainbowRunnerEffect::begin() {
  pos = 0;
  dir = 1;
  hue = 0;
}

uint16_t RainbowRunnerEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void RainbowRunnerEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  for (uint16_t i = 0; i < n; i++) {
    strip.setPixelColor(i, fadeColor(strip.getPixelColor(i), 3));
  }
  pos += dir;
  if (pos >= (int16_t)n - 1) {
    pos = (int16_t)n - 1;
    dir = -1;
  }
  if (pos <= 0) {
    pos = 0;
    dir = 1;
  }
  uint32_t c = wheel(hue);
  strip.setPixelColor((uint16_t)pos, c);
  uint16_t trail = (uint16_t)(pos - dir);
  if (trail < n) {
    strip.setPixelColor(trail, scaleColor(c, 140));
  }
  hue += 3;
}

const __FlashStringHelper* RainbowRunnerEffect::name() const {
  return F("rainbowrunner");
}

static RainbowRunnerEffect s_instance;
IEffect& rainbowRunnerEffect = s_instance;