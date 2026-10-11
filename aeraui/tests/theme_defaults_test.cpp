/* Copyright (C) 2026 AERA Recovery Project contributors
 * SPDX-License-Identifier: Apache-2.0 */
#include <aeraui/theme_defaults.hpp>

#include <cassert>
#include <cstring>

static_assert(aeraui::theme::kDefaultAccentRgb == EXPECT_DEFAULT_ACCENT_RGB,
              "Native rendering must use the configured device default");

int main() {
  assert(std::strcmp(aeraui::theme::kDefaultAccentHex,
                     EXPECT_DEFAULT_ACCENT_HEX) == 0);
  const char *invalid_values[] = {nullptr, "", "000000", "ff690", "ff69000",
                                  "#ff6900", "0xff6900", "gg6900"};
  for (const char *invalid : invalid_values) {
    assert(aeraui::theme::AccentOrDefault(invalid) ==
           EXPECT_DEFAULT_ACCENT_RGB);
  }
  // A saved user color must survive either the stock or orange build default.
  assert(aeraui::theme::AccentOrDefault("22ddee") == 0x22ddee);
  assert(aeraui::theme::AccentOrDefault("22DDEE") == 0x22ddee);
  assert(aeraui::theme::AccentOrDefault("000001") == 0x000001);
}
