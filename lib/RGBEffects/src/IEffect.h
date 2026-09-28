#pragma once

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

struct RenderParams {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t brightness;
  uint8_t speed;
};

class IEffect {
public:
  virtual ~IEffect() {}
  virtual void begin() = 0;
  virtual uint16_t intervalMs(uint8_t speed) const = 0;
  virtual void update(Adafruit_NeoPixel& strip, const RenderParams& p) = 0;
  virtual const __FlashStringHelper* name() const = 0;
};

inline uint8_t scaleChannel(uint8_t ch, uint8_t scale) {
  return (uint8_t)(((uint16_t)ch * scale) >> 8);
}

inline uint32_t scaleColor(uint32_t c, uint8_t scale) {
  return ((uint32_t)scaleChannel((uint8_t)(c >> 16), scale) << 16) |
         ((uint32_t)scaleChannel((uint8_t)(c >> 8), scale) << 8) |
         ((uint32_t)scaleChannel((uint8_t)c, scale));
}

inline uint32_t fadeColor(uint32_t c, uint8_t shift) {
  uint8_t r = (c >> 16) & 0xFF;
  uint8_t g = (c >> 8) & 0xFF;
  uint8_t b = c & 0xFF;
  r -= r >> shift;
  g -= g >> shift;
  b -= b >> shift;
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

inline uint32_t wheel(uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85) return ((uint32_t)(255 - pos * 3) << 16);
  if (pos < 170) {
    pos -= 85;
    return ((uint32_t)0 << 16) | ((uint32_t)(pos * 3) << 8) | (uint32_t)(255 - pos * 3);
  }
  pos -= 170;
  return ((uint32_t)(pos * 3) << 16) | ((uint32_t)(255 - pos * 3) << 8);
}

inline uint16_t defaultInterval(uint8_t speed) {
  return (uint16_t)(320U - 30U * (speed - 1));
}

inline uint16_t fastInterval(uint8_t speed) {
  return (uint16_t)(200U - 18U * (speed - 1));
}

inline uint16_t slowInterval(uint8_t speed) {
  return (uint16_t)(640U - 60U * (speed - 1));
}