#include "TrafficEffect.h"

void TrafficEffect::begin() {
  phase = 0;
}

uint16_t TrafficEffect::intervalMs(uint8_t speed) const {
  (void)speed;
  return 50;
}

void TrafficEffect::update(Adafruit_NeoPixel& strip, const RenderParams& p) {
  (void)p;
  uint8_t seg = (uint8_t)(phase / kTicksPerLight);
  uint32_t c;
  if (seg == 0) c = strip.Color(255, 0, 0);
  else if (seg == 1) c = strip.Color(255, 160, 0);
  else c = strip.Color(0, 255, 0);
  if ((phase % 20) >= 10) c = scaleColor(c, 60);
  strip.fill(c, 0, strip.numPixels());
  phase++;
  if (phase >= (uint32_t)3 * kTicksPerLight) phase = 0;
}

const __FlashStringHelper* TrafficEffect::name() const {
  return F("traffic");
}

static TrafficEffect s_instance;
IEffect& trafficEffect = s_instance;