#pragma once
#include <Arduino.h>
#include <esp_sleep.h>

static constexpr uint8_t KEY0 = 5;  // GPIO5
static constexpr uint8_t KEY1 = 4;  // GPIO4
static constexpr uint8_t KEY2 = 3;  // GPIO3

inline void pagewake_setup_pins() {
  pinMode(KEY0, INPUT_PULLUP);
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
}

// returns: 0=overview, 1=climate, 2=homelab
// Uses the ext1 wake status, so a short tap is enough (no need to hold the key).
inline int pagewake_select_page_default_0() {
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1) {
    const uint64_t mask = esp_sleep_get_ext1_wakeup_status();
    if (mask & (1ULL << KEY0)) return 1;  // KEY0 -> Climate
    if (mask & (1ULL << KEY1)) return 2;  // KEY1 -> Homelab
    return 0;                             // KEY2 -> Overview
  }

  // Timer wake / power-on: fall back to a held key, otherwise Overview
  if (digitalRead(KEY0) == LOW) return 1;
  if (digitalRead(KEY1) == LOW) return 2;
  return 0;
}
