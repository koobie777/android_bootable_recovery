// Copyright (C) 2026 AERA Recovery Project contributors
// SPDX-License-Identifier: Apache-2.0

package twrp

import (
	"fmt"
	"strconv"
	"strings"
)

// Keep validation independent of Soong so malformed device settings can be
// checked without loading an Android product or generating its build graph.
func aeraDefaultAccentFlag(value string) (string, error) {
	value = strings.TrimSpace(value)
	if value == "" {
		return "", nil
	}
	if len(value) == 6 {
		if rgb, err := strconv.ParseUint(value, 16, 24); err == nil && rgb != 0 {
			return fmt.Sprintf("-DAERA_DEFAULT_ACCENT=0x%06x", rgb), nil
		}
	}
	return "", fmt.Errorf("AERA_DEFAULT_ACCENT must contain exactly six RGB hex digits without # or 0x and cannot be 000000 (for example ff6900); got %q", value)
}
