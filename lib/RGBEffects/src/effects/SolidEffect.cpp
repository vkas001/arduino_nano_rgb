#include "SolidEffect.h"

void SolidEffect::begin() {}

uint16_t SolidEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void SolidEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  strip.fill(strip.Color(p.red, p.green, p.blue), 0, strip.numPixels());
}

const __FlashStringHelper* SolidEffect::name() const {
  return F("solid");
}

static SolidEffect s_instance;
IEffect& solidEffect = s_instance;