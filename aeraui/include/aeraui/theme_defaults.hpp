/* Copyright (C) 2026 AERA Recovery Project contributors
 * SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <cstdint>

// Device trees may override this through AERA_DEFAULT_ACCENT (six hex digits).
// Saved preferences take precedence; this is only the first-start/reset default.
#ifndef AERA_DEFAULT_ACCENT
#define AERA_DEFAULT_ACCENT 0x16c8ff
#endif

namespace aeraui::theme {

inline constexpr uint32_t kDefaultAccentRgb = AERA_DEFAULT_ACCENT;
static_assert(kDefaultAccentRgb > 0 && kDefaultAccentRgb <= 0x00ffffff,
              "AERA_DEFAULT_ACCENT must be a nonzero 24-bit RGB color");

constexpr char HexDigit(uint32_t value) {
  return "0123456789abcdef"[value & 0xf];
}

// Derive the preference form from the same RGB constant as native rendering.
inline constexpr char kDefaultAccentHex[] = {
    HexDigit(kDefaultAccentRgb >> 20), HexDigit(kDefaultAccentRgb >> 16),
    HexDigit(kDefaultAccentRgb >> 12), HexDigit(kDefaultAccentRgb >> 8),
    HexDigit(kDefaultAccentRgb >> 4), HexDigit(kDefaultAccentRgb), '\0'};

// Preference writers use six hex digits. A saved valid color always wins over
// the device default; missing or malformed values use the same reset default.
constexpr uint32_t AccentOrDefault(const char *value) {
  if (value == nullptr) return kDefaultAccentRgb;
  uint32_t rgb = 0;
  for (int i = 0; i < 6; ++i) {
    const char digit = value[i];
    if (digit >= '0' && digit <= '9') rgb = (rgb << 4) | (digit - '0');
    else if (digit >= 'a' && digit <= 'f') rgb = (rgb << 4) | (digit - 'a' + 10);
    else if (digit >= 'A' && digit <= 'F') rgb = (rgb << 4) | (digit - 'A' + 10);
    else return kDefaultAccentRgb;
  }
  return value[6] == '\0' && rgb != 0 ? rgb : kDefaultAccentRgb;
}

}  // namespace aeraui::theme
