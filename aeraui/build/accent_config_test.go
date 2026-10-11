// Copyright (C) 2026 AERA Recovery Project contributors
// SPDX-License-Identifier: Apache-2.0

package twrp

import "testing"

func TestDefaultAccentFlag(t *testing.T) {
	for _, test := range []struct {
		input string
		want  string
	}{
		{"", ""},
		{" \t", ""},
		{"ff6900", "-DAERA_DEFAULT_ACCENT=0xff6900"},
		{"FF6900", "-DAERA_DEFAULT_ACCENT=0xff6900"},
		{"000001", "-DAERA_DEFAULT_ACCENT=0x000001"},
		{"ffffff", "-DAERA_DEFAULT_ACCENT=0xffffff"},
		{" 16c8ff ", "-DAERA_DEFAULT_ACCENT=0x16c8ff"},
	} {
		t.Run(test.input, func(t *testing.T) {
			got, err := aeraDefaultAccentFlag(test.input)
			if err != nil || got != test.want {
				t.Fatalf("aeraDefaultAccentFlag(%q) = %q, %v; want %q", test.input, got, err, test.want)
			}
		})
	}
}

func TestDefaultAccentRejectsInvalidDeviceValues(t *testing.T) {
	for _, input := range []string{
		"000000", "ff690", "ff69000", "#ff6900", "0xff6900", "ff69gg",
		"+f6900", "-f6900", "ff_900", "ff 900", "\"ff6900\"", "ff6900;exit",
	} {
		t.Run(input, func(t *testing.T) {
			flag, err := aeraDefaultAccentFlag(input)
			if err == nil || flag != "" {
				t.Fatalf("aeraDefaultAccentFlag(%q) = %q, %v; want an error and no compiler flag", input, flag, err)
			}
		})
	}
}
