#pragma once

#include "../IEffect.h"

class CometEffect : public IEffect {
  int16_t pos = 0;
  int8_t dir = 1;
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& cometEffect;