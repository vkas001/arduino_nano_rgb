#include "StrobeEffect.h"

void StrobeEffect::begin() {
  counter = 0;
}

uint16_t StrobeEffect::intervalMs(uint8_t speed) const {
  return fastInterval(speed);
}

void StrobeEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  counter = (counter + 1) % 3;
  if (counter == 0) {
    strip.fill(strip.Color(p.red, p.green, p.blue), 0, strip.numPixels());
  } else {
    strip.fill(strip.Color(0, 0, 0), 0, strip.numPixels());
  }
}

const __FlashStringHelper* StrobeEffect::name() const {
  return F("strobe");
}

static StrobeEffect s_instance;
IEffect& strobeEffect = s_instance;