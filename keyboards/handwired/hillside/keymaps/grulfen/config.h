/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

// How long until hold action happens
#define TAPPING_TERM 200

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

#define ONESHOT_TIMEOUT 1000  // Time in ms before the one shot key is released
#define ONESHOT_TAP_TOGGLE 5  // tapping this number of times holds the key until tapped once

// Use shift instead of capslock for caps_word
#define CAPSWORD_USE_SHIFT
