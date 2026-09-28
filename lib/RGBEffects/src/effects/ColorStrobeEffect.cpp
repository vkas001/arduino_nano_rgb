#include "ColorStrobeEffect.h"

void ColorStrobeEffect::begin() {
  counter = 0;
  hue = 0;
}

uint16_t ColorStrobeEffect::intervalMs(uint8_t speed) const {
  return fastInterval(speed);
}

void ColorStrobeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  counter = (counter + 1) % 3;
  if (counter == 0) {
    uint32_t c = wheel(hue);
    strip.fill(c, 0, strip.numPixels());
    hue = (uint8_t)(hue + 24);
  } else {
    strip.fill(strip.Color(0, 0, 0), 0, strip.numPixels());
  }
}

const __FlashStringHelper* ColorStrobeEffect::name() const {
  return F("colorstrobe");
}

static ColorStrobeEffect s_instance;
IEffect& colorStrobeEffect = s_instance;