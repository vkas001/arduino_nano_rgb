#pragma once

#include "../IEffect.h"

class RipplesEffect : public IEffect {
  struct Ripple {
    int16_t center;
    uint8_t age;
    uint8_t active;
  };
  static const uint8_t kRipples = 4;
  Ripple ripple[kRipples];
public:
  void begin() override;
  uint16_t intervalMs(uint8_t speed) const override;
  void update(Adafruit_NeoPixel& strip, const RenderParams& p) override;
  const __FlashStringHelper* name() const override;
};

extern IEffect& ripplesEffect;