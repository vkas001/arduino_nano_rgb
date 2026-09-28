#pragma once

#include "../IEffect.h"

class FireworksEffect : public IEffect {
  uint8_t phase = 0;
  uint16_t pos = 0;
  uint16_t ring = 0;
  int16_t center = 0;
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& fireworksEffect;