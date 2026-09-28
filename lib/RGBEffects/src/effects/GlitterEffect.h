#pragma once

#include "../IEffect.h"

class GlitterEffect : public IEffect {
  static const uint8_t kSlots = 6;
  int16_t sx[kSlots] = {};
  uint8_t sb[kSlots] = {};
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& glitterEffect;