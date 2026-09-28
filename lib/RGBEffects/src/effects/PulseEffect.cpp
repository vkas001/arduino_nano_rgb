#include "PulseEffect.h"

void PulseEffect::begin() {
  lit = true;
}

uint16_t PulseEffect::intervalMs(uint8_t speed) const {
  return defaultInterval(speed);
}

void PulseEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  strip.fill(lit ? strip.Color(p.red, p.green, p.blue) : strip.Color(0, 0, 0), 0, strip.numPixels());
  lit = !lit;
}

const __FlashStringHelper* PulseEffect::name() const {
  return F("pulse");
}

static PulseEffect s_instance;
IEffect& pulseEffect = s_instance;