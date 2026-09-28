#include "SnakeEffect.h"

void SnakeEffect::begin() {
  head = 0;
}

uint16_t SnakeEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void SnakeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  uint16_t n = strip.numPixels();
  uint32_t c = strip.Color(p.red, p.green, p.blue);
  if (n == 0) return;
  uint8_t len = (uint8_t)(5 + p.speed / 2);
  for (uint16_t i = 0; i < n; i++) {
    uint16_t d = (uint16_t)((i + n - head) % n);
    if (d < len) {
      uint8_t s = (uint8_t)((len - d) * 255 / len);
      strip.setPixelColor(i, scaleColor(c, s));
    } else {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  head++;
  if (head >= n) head = 0;
}

const __FlashStringHelper* SnakeEffect::name() const {
  return F("snake");
}

static SnakeEffect s_instance;
IEffect& snakeEffect = s_instance;