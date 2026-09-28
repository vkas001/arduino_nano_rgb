#pragma once

#include <stdint.h>
#include "IEffect.h"

namespace Effects {
  uint8_t count();
  IEffect* get(uint8_t index);
  int8_t indexOf(const char* name);
}