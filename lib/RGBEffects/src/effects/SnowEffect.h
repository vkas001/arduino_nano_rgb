#pragma once

#include "../IEffect.h"

#ifndef NUM_LEDS
#define NUM_LEDS 60
#endif

class SnowEffect : public IEffect {
  uint8_t flake[NUM_LEDS] = {};
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& snowEffect;