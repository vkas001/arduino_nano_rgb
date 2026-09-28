#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <RGBEffects.h>
#include "config.h"

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED_STRIP, NEO_GRB + NEO_KHZ800);

static uint8_t red = 255;
static uint8_t green = 0;
static uint8_t blue = 150;
static uint8_t brightness = 128;
static uint8_t speed = 5;
static uint8_t effectIndex = 0;
static bool power = true;
static bool cycle = false;
static RenderParams params;

static unsigned long lastAnimMs = 0;
static unsigned long lastCycleMs = 0;
static unsigned long lastPotMs = 0;

static char rxBuffer[40];
static uint8_t rxIndex = 0;

static void switchEffect(uint8_t index) {
  effectIndex = index;
  IEffect* e = Effects::get(effectIndex);
  if (e) e->begin();
  lastCycleMs = millis();
}

static void renderNow() {
  if (!power) {
    strip.fill(strip.Color(0, 0, 0), 0, NUM_LEDS);
    strip.show();
    return;
  }
  if (effectIndex == 0) {
    strip.setBrightness(brightness);
    Effects::get(effectIndex)->update(strip, params);
  }
}

static bool readButton(uint8_t pin, bool &state, unsigned long &lastMs) {
  bool raw = digitalRead(pin) == LOW;
  if (raw != state) {
    lastMs = millis();
    state = raw;
  } else if (raw && (millis() - lastMs) >= DEBOUNCE_MS) {
    return true;
  }
  return false;
}

static void handlePhysical() {
  static bool sPowerBtn = HIGH;
  static bool sEffectBtn = HIGH;
  static unsigned long pPowerMs = 0;
  static unsigned long pEffectMs = 0;

  if (readButton(PIN_BTN_POWER, sPowerBtn, pPowerMs)) {
    power = !power;
    Serial.print(F("[btn] power "));
    Serial.println(power ? F("on") : F("off"));
    renderNow();
  }
  if (readButton(PIN_BTN_EFFECT, sEffectBtn, pEffectMs)) {
    switchEffect((uint8_t)((effectIndex + 1) % Effects::count()));
    cycle = false;
    Serial.print(F("[btn] effect -> "));
    Serial.println(Effects::get(effectIndex)->name());
    renderNow();
  }

  if (millis() - lastPotMs < 100) return;
  lastPotMs = millis();
  int potBright = analogRead(PIN_POT_BRIGHT);
  int potSpeed = analogRead(PIN_POT_SPEED);
  uint8_t newBright = (uint8_t)map(potBright, 0, POT_RESOLUTION - 1, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  uint8_t newSpeed = (uint8_t)map(potSpeed, 0, POT_RESOLUTION - 1, SPEED_MIN, SPEED_MAX);
  if (newBright != brightness) {
    brightness = newBright;
    strip.setBrightness(brightness);
    if (effectIndex == 0) renderNow();
  }
  if (newSpeed != speed) {
    speed = newSpeed;
  }
  params.brightness = brightness;
  params.speed = speed;
}

static void printStatus() {
  Serial.print(F("power="));
  Serial.print(power ? F("on") : F("off"));
  Serial.print(F("  color=#"));
  if (red < 16) Serial.print('0');
  Serial.print(red, HEX);
  if (green < 16) Serial.print('0');
  Serial.print(green, HEX);
  if (blue < 16) Serial.print('0');
  Serial.print(blue, HEX);
  Serial.print(F("  brightness="));
  Serial.print(brightness);
  Serial.print(F("  speed="));
  Serial.print(speed);
  Serial.print(F("  effect="));
  Serial.print(Effects::get(effectIndex)->name());
  Serial.print(F(" ("));
  Serial.print(effectIndex);
  Serial.print(F("/"));
  Serial.print(Effects::count() - 1);
  Serial.print(F(")  cycle="));
  Serial.println(cycle ? F("on") : F("off"));
}

static void printHelp() {
  Serial.println(F("Commands (newline terminated):"));
  Serial.println(F("  on | off                     power state"));
  Serial.println(F("  color RRGGBB                 set color (hex)"));
  Serial.println(F("  color R G B                  set color (0-255 each)"));
  Serial.println(F("  brightness N                 set brightness 0-255"));
  Serial.println(F("  effect NAME | N              select effect"));
  Serial.println(F("  effect list                  list all effects"));
  Serial.println(F("  speed N                      set speed 1-10"));
  Serial.println(F("  cycle on | off | SECONDS     auto-advance effects (or 'cycle' to toggle)"));
  Serial.println(F("  status                       show current settings"));
  Serial.println(F("  help                         this help"));
}

static void handleCommand(char *line) {
  char *tok = strtok(line, " \t");
  if (!tok) return;

  if (strcasecmp(tok, "on") == 0) {
    power = true;
    renderNow();
    Serial.println(F("on"));
  } else if (strcasecmp(tok, "off") == 0) {
    power = false;
    renderNow();
    Serial.println(F("off"));
  } else if (strcasecmp(tok, "color") == 0) {
    char *a = strtok(NULL, " \t");
    char *b = strtok(NULL, " \t");
    char *c = strtok(NULL, " \t");
    if (!a) {
      Serial.println(F("usage: color RRGGBB | color R G B"));
      return;
    }
    if (b && c) {
      red = (uint8_t)strtoul(a, NULL, 10);
      green = (uint8_t)strtoul(b, NULL, 10);
      blue = (uint8_t)strtoul(c, NULL, 10);
    } else {
      uint32_t hex = strtoul(a, NULL, 16);
      red = (uint8_t)((hex >> 16) & 0xFF);
      green = (uint8_t)((hex >> 8) & 0xFF);
      blue = (uint8_t)(hex & 0xFF);
    }
    Serial.print(F("color #"));
    if (red < 16) Serial.print('0');
    Serial.print(red, HEX);
    if (green < 16) Serial.print('0');
    Serial.print(green, HEX);
    if (blue < 16) Serial.print('0');
    Serial.println(blue, HEX);
    renderNow();
  } else if (strcasecmp(tok, "brightness") == 0) {
    char *arg = strtok(NULL, " \t");
    if (arg) {
      long v = strtol(arg, NULL, 10);
      brightness = (uint8_t)constrain(v, 0L, 255L);
      if (brightness < MIN_BRIGHTNESS) brightness = MIN_BRIGHTNESS;
      strip.setBrightness(brightness);
      renderNow();
      Serial.print(F("brightness="));
      Serial.println(brightness);
    }
  } else if (strcasecmp(tok, "effect") == 0) {
    char *arg = strtok(NULL, " \t");
    if (!arg) {
      Serial.println(F("usage: effect NAME | N | list"));
      return;
    }
    if (strcasecmp(arg, "list") == 0) {
      for (uint8_t i = 0; i < Effects::count(); i++) {
        Serial.print(i);
        Serial.print(F(" "));
        Serial.println(Effects::get(i)->name());
      }
      return;
    }
    int8_t idx = (int8_t)atoi(arg);
    if (idx < 0 || idx >= (int8_t)Effects::count()) {
      idx = Effects::indexOf(arg);
    }
    if (idx < 0 || idx >= (int8_t)Effects::count()) {
      Serial.println(F("unknown effect"));
      return;
    }
    switchEffect((uint8_t)idx);
    cycle = false;
    Serial.print(F("effect="));
    Serial.println(Effects::get(effectIndex)->name());
    renderNow();
  } else if (strcasecmp(tok, "speed") == 0) {
    char *arg = strtok(NULL, " \t");
    if (arg) {
      speed = (uint8_t)constrain(strtol(arg, NULL, 10), SPEED_MIN, SPEED_MAX);
      Serial.print(F("speed="));
      Serial.println(speed);
    }
  } else if (strcasecmp(tok, "cycle") == 0) {
    char *arg = strtok(NULL, " \t");
    if (!arg || strcasecmp(arg, "on") == 0) {
      cycle = true;
    } else if (strcasecmp(arg, "off") == 0) {
      cycle = false;
    }
    Serial.print(F("cycle="));
    Serial.println(cycle ? F("on") : F("off"));
  } else if (strcasecmp(tok, "status") == 0) {
    printStatus();
  } else if (strcasecmp(tok, "help") == 0) {
    printHelp();
  } else {
    Serial.println(F("unknown command (type 'help')"));
  }
}

static void pollSerial() {
  while (Serial.available()) {
    char ch = (char)Serial.read();
    if (ch == '\n' || ch == '\r') {
      if (rxIndex > 0) {
        rxBuffer[rxIndex] = '\0';
        handleCommand(rxBuffer);
        rxIndex = 0;
      }
    } else if (rxIndex < sizeof(rxBuffer) - 1) {
      rxBuffer[rxIndex++] = ch;
    }
  }
}

void setup() {
  pinMode(PIN_BTN_POWER, INPUT_PULLUP);
  pinMode(PIN_BTN_EFFECT, INPUT_PULLUP);
  pinMode(PIN_POT_BRIGHT, INPUT);
  pinMode(PIN_POT_SPEED, INPUT);

  Serial.begin(SERIAL_BAUD);
  strip.begin();
  strip.setBrightness(brightness);

  randomSeed(analogRead(PIN_POT_SPEED));

  params.red = red;
  params.green = green;
  params.blue = blue;
  params.brightness = brightness;
  params.speed = speed;

  Effects::get(effectIndex)->begin();
  lastCycleMs = millis();

  Serial.println(F("RGB strip controller ready"));
  printHelp();
  renderNow();
}

void loop() {
  params.red = red;
  params.green = green;
  params.blue = blue;

  pollSerial();
  handlePhysical();

  unsigned long now = millis();
  IEffect* e = Effects::get(effectIndex);

  if (power && e && now - lastAnimMs >= e->intervalMs(speed)) {
    lastAnimMs = now;
    lastCycleMs = now;
    strip.setBrightness(brightness);
    e->update(strip, params);
  }

  if (cycle && now - lastCycleMs >= (unsigned long)CYCLE_SECONDS * 1000UL) {
    switchEffect((uint8_t)((effectIndex + 1) % Effects::count()));
    Serial.print(F("[cycle] effect -> "));
    Serial.println(Effects::get(effectIndex)->name());
  }
}