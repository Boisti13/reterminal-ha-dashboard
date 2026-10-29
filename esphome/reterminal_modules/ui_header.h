#pragma once
#include "esphome.h"
#include <cmath>
#include <cstdio>
#include <string>

// "2026-09-22T09:52:22+00:00" (UTC, as HA sends timestamps) -> epoch seconds, -1 if unparsable
inline long iso_utc_to_epoch(const std::string &iso) {
  int Y, M, D, h, m, s;
  if (sscanf(iso.c_str(), "%d-%d-%dT%d:%d:%d", &Y, &M, &D, &h, &m, &s) != 6) return -1;
  // days_from_civil (Howard Hinnant)
  Y -= M <= 2;
  const int era = (Y >= 0 ? Y : Y - 399) / 400;
  const unsigned yoe = (unsigned) (Y - era * 400);
  const unsigned doy = (153 * (M + (M > 2 ? -3 : 9)) + 2) / 5 + D - 1;
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  const long days = (long) era * 146097 + (long) doe - 719468;
  return days * 86400L + h * 3600L + m * 60L + s;
}

// Shared page header: centered date, battery icon + percent (top right), divider line.
// Fonts are passed in because id() objects are not declared yet when this file is included.

inline const char *battery_icon_for(float level) {
  if (std::isnan(level)) return "\U000F0082";  // fallback (90)
  if (level >= 95) return "\U000F0079";        // full
  if (level >= 85) return "\U000F0082";        // 90
  if (level >= 75) return "\U000F0081";        // 80
  if (level >= 65) return "\U000F0080";        // 70
  if (level >= 55) return "\U000F007F";        // 60
  if (level >= 45) return "\U000F007E";        // 50
  if (level >= 35) return "\U000F007D";        // 40
  if (level >= 25) return "\U000F007C";        // 30
  if (level >= 15) return "\U000F007B";        // 20
  if (level >=  5) return "\U000F007A";        // 10
  return "\U000F0083";                         // critical
}

inline void draw_header(esphome::display::Display &it,
                        esphome::font::Font *f_date,
                        esphome::font::Font *f_pct,
                        esphome::font::Font *f_bat,
                        esphome::ESPTime now,
                        float bat_level,
                        const char *fallback_title) {
  using esphome::display::COLOR_ON;
  using esphome::display::TextAlign;

  const int WIDTH    = 800;
  const int MARGIN   = 20;
  const int HEADER_Y = 10;

  // Date (centered)
  if (now.is_valid()) {
    it.print(WIDTH / 2, HEADER_Y, f_date, COLOR_ON, TextAlign::TOP_CENTER, now.strftime("%A %d.%m").c_str());
  } else {
    it.print(WIDTH / 2, HEADER_Y, f_date, COLOR_ON, TextAlign::TOP_CENTER, fallback_title);
  }

  // Battery icon + percent centered under it
  const int x = WIDTH - MARGIN - 25;
  const int y = HEADER_Y + 2;
  const int icon_px = 20;  // must match battery icon font size
  it.print(x, y, f_bat, COLOR_ON, battery_icon_for(bat_level));
  if (!std::isnan(bat_level)) {
    it.printf(x + icon_px / 2, y + icon_px + 2, f_pct, COLOR_ON, TextAlign::TOP_CENTER, "%.0f%%", bat_level);
  } else {
    it.print(x + icon_px / 2, y + icon_px + 2, f_pct, COLOR_ON, TextAlign::TOP_CENTER, "--");
  }

  // Low battery note left of the icon (device sleeps 6h instead of 2h below this level)
  const float LOW_BATTERY_PCT = 15.0f;  // keep in sync with reterminal.yaml sleep_duration lambda
  if (!std::isnan(bat_level) && bat_level < LOW_BATTERY_PCT) {
    it.print(x - 8, y + 4, f_pct, COLOR_ON, TextAlign::TOP_RIGHT, "Charge battery");
  }

  // Divider
  it.line(MARGIN, 50, WIDTH - MARGIN, 50, COLOR_ON);
}
