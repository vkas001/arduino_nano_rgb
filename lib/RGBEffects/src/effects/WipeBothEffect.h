#pragma once

#include "../IEffect.h"

class WipeBothEffect : public IEffect {
  uint16_t pos = 0;
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& wipeBothEffect;