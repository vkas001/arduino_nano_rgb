#pragma once

#include "../IEffect.h"

#ifndef NUM_LEDS
#define NUM_LEDS 60
#endif

class BounceEffect : public IEffect {
  static const uint8_t kBalls = 3;
  int16_t x[kBalls];
  int8_t dir[kBalls];
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& bounceEffect;