#include "RGBEffects.h"
#include <Arduino.h>

#include "effects/SolidEffect.h"
#include "effects/BreathEffect.h"
#include "effects/PulseEffect.h"
#include "effects/StrobeEffect.h"
#include "effects/RainbowEffect.h"
#include "effects/RainbowFadeEffect.h"
#include "effects/RainbowChaseEffect.h"
#include "effects/RainbowWipeEffect.h"
#include "effects/WipeEffect.h"
#include "effects/ChaseEffect.h"
#include "effects/TwinkleEffect.h"
#include "effects/SparkleEffect.h"
#include "effects/CometEffect.h"
#include "effects/ScannerEffect.h"
#include "effects/BounceEffect.h"
#include "effects/FlowEffect.h"
#include "effects/FireEffect.h"
#include "effects/FireworksEffect.h"
#include "effects/PartyEffect.h"
#include "effects/CopEffect.h"
#include "effects/ChristmasEffect.h"
#include "effects/MarqueeEffect.h"
#include "effects/RainEffect.h"
#include "effects/NoiseEffect.h"
#include "effects/GlitterEffect.h"
#include "effects/SnowEffect.h"
#include "effects/RainbowRunnerEffect.h"
#include "effects/RipplesEffect.h"
#include "effects/WavesEffect.h"
#include "effects/SnakeEffect.h"
#include "effects/TrafficEffect.h"
#include "effects/BeaconEffect.h"
#include "effects/ColorStrobeEffect.h"
#include "effects/RainbowMarqueeEffect.h"
#include "effects/CrossfadeEffect.h"
#include "effects/WipeBothEffect.h"
#include "effects/CandleEffect.h"

namespace Effects {

static IEffect* const kAll[] = {
  &solidEffect, &breathEffect, &pulseEffect, &strobeEffect,
  &rainbowEffect, &rainbowFadeEffect, &rainbowChaseEffect, &rainbowWipeEffect,
  &wipeEffect, &chaseEffect, &twinkleEffect, &sparkleEffect,
  &cometEffect, &scannerEffect, &bounceEffect, &flowEffect,
  &fireEffect, &fireworksEffect, &partyEffect, &copEffect,
  &christmasEffect, &marqueeEffect, &rainEffect, &noiseEffect,
  &glitterEffect, &snowEffect, &rainbowRunnerEffect, &ripplesEffect,
  &wavesEffect, &snakeEffect, &trafficEffect, &beaconEffect,
  &colorStrobeEffect, &rainbowMarqueeEffect, &crossfadeEffect,
  &wipeBothEffect, &candleEffect,
};

uint8_t count() {
  return (uint8_t)(sizeof(kAll) / sizeof(kAll[0]));
}

IEffect* get(uint8_t index) {
  return (index < count()) ? kAll[index] : NULL;
}

int8_t indexOf(const char* s) {
  for (uint8_t i = 0; i < count(); i++) {
    if (strcmp_P(s, (PGM_P)kAll[i]->name()) == 0) {
      return (int8_t)i;
    }
  }
  return -1;
}

}  // namespace Effects