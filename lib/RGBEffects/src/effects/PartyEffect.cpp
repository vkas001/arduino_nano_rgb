#include "PartyEffect.h"
#include <Arduino.h>

void PartyEffect::begin() {}

uint16_t PartyEffect::intervalMs(uint8_t speed) const {
  return fastInterval(speed);
}

void PartyEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint16_t n = strip.numPixels();
  for (uint16_t i = 0; i < n; i++) {
    if (random(0, 3) != 0) {
      strip.setPixelColor(i, random(0, 256), random(0, 256), random(0, 256));
    }
  }
}

const __FlashStringHelper* PartyEffect::name() const {
  return F("party");
}

static PartyEffect s_instance;
IEffect& partyEffect = s_instance;