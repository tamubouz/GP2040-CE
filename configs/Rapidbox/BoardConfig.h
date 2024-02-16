/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef PICO_BOARD_CONFIG_H_
#define PICO_BOARD_CONFIG_H_

#include "enums.pb.h"
#include "class/hid/hid.h"

#define BOARD_CONFIG_LABEL "Rapidbox"

// Main pin mapping Configuration
//                                                  // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
// #define GPIO_PIN_02 GpioAction::BUTTON_PRESS_UP     // UP     | UP     | UP      | UP       | UP     | UP     |
// #define GPIO_PIN_03 GpioAction::BUTTON_PRESS_DOWN   // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
// #define GPIO_PIN_04 GpioAction::BUTTON_PRESS_RIGHT  // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
// #define GPIO_PIN_05 GpioAction::BUTTON_PRESS_LEFT   // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |
// #define GPIO_PIN_06 GpioAction::BUTTON_PRESS_B1     // B1     | A      | B       | Cross    | 2      | K1     |
// #define GPIO_PIN_07 GpioAction::BUTTON_PRESS_B2     // B2     | B      | A       | Circle   | 3      | K2     |
// #define GPIO_PIN_17 GpioAction::BUTTON_PRESS_R2     // R2     | RT     | ZR      | R2       | 8      | K3     |
// #define GPIO_PIN_09 GpioAction::BUTTON_PRESS_L2     // L2     | LT     | ZL      | L2       | 7      | K4     |
// #define GPIO_PIN_10 GpioAction::BUTTON_PRESS_B3     // B3     | X      | Y       | Square   | 1      | P1     |
// #define GPIO_PIN_11 GpioAction::BUTTON_PRESS_B4     // B4     | Y      | X       | Triangle | 4      | P2     |
// #define GPIO_PIN_12 GpioAction::BUTTON_PRESS_R1     // R1     | RB     | R       | R1       | 6      | P3     |
// #define GPIO_PIN_13 GpioAction::BUTTON_PRESS_L1     // L1     | LB     | L       | L1       | 5      | P4     |
#define GPIO_PIN_09 GpioAction::BUTTON_PRESS_S2     // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define GPIO_PIN_08 GpioAction::BUTTON_PRESS_S1     // S2     | Start  | Plus    | Start    | 10     | Start  |
// #define GPIO_PIN_18 GpioAction::BUTTON_PRESS_L3     // L3     | LS     | LS      | L3       | 11     | LS     |
// #define GPIO_PIN_19 GpioAction::BUTTON_PRESS_R3     // R3     | RS     | RS      | R3       | 12     | RS     |
#define GPIO_PIN_07 GpioAction::BUTTON_PRESS_A2     // A1     | Guide  | Home    | PS       | 13     | ~      |
#define GPIO_PIN_06 GpioAction::BUTTON_PRESS_A1     // A2     | ~      | Capture | ~        | 14     | ~      |

// Keyboard Mapping Configuration
//                                            // GP2040 | Xinput | Switch  | PS3/4/5  | Dinput | Arcade |
#define KEY_DPAD_UP     HID_KEY_ARROW_UP      // UP     | UP     | UP      | UP       | UP     | UP     |
#define KEY_DPAD_DOWN   HID_KEY_ARROW_DOWN    // DOWN   | DOWN   | DOWN    | DOWN     | DOWN   | DOWN   |
#define KEY_DPAD_RIGHT  HID_KEY_ARROW_RIGHT   // RIGHT  | RIGHT  | RIGHT   | RIGHT    | RIGHT  | RIGHT  |
#define KEY_DPAD_LEFT   HID_KEY_ARROW_LEFT    // LEFT   | LEFT   | LEFT    | LEFT     | LEFT   | LEFT   |
#define KEY_BUTTON_B1   HID_KEY_SHIFT_LEFT    // B1     | A      | B       | Cross    | 2      | K1     |
#define KEY_BUTTON_B2   HID_KEY_Z             // B2     | B      | A       | Circle   | 3      | K2     |
#define KEY_BUTTON_R2   HID_KEY_X             // R2     | RT     | ZR      | R2       | 8      | K3     |
#define KEY_BUTTON_L2   HID_KEY_V             // L2     | LT     | ZL      | L2       | 7      | K4     |
#define KEY_BUTTON_B3   HID_KEY_CONTROL_LEFT  // B3     | X      | Y       | Square   | 1      | P1     |
#define KEY_BUTTON_B4   HID_KEY_ALT_LEFT      // B4     | Y      | X       | Triangle | 4      | P2     |
#define KEY_BUTTON_R1   HID_KEY_SPACE         // R1     | RB     | R       | R1       | 6      | P3     |
#define KEY_BUTTON_L1   HID_KEY_C             // L1     | LB     | L       | L1       | 5      | P4     |
#define KEY_BUTTON_S1   HID_KEY_5             // S1     | Back   | Minus   | Select   | 9      | Coin   |
#define KEY_BUTTON_S2   HID_KEY_1             // S2     | Start  | Plus    | Start    | 10     | Start  |
#define KEY_BUTTON_L3   HID_KEY_EQUAL         // L3     | LS     | LS      | L3       | 11     | LS     |
#define KEY_BUTTON_R3   HID_KEY_MINUS         // R3     | RS     | RS      | R3       | 12     | RS     |
#define KEY_BUTTON_A1   HID_KEY_9             // A1     | Guide  | Home    | PS       | 13     | ~      |
#define KEY_BUTTON_A2   HID_KEY_F2            // A2     | ~      | Capture | ~        | 14     | ~      |
#define KEY_BUTTON_FN   -1                    // Hotkey Function                                        |

#define HAS_I2C_DISPLAY 1
#define I2C1_ENABLED 1
#define I2C1_PIN_SDA 26
#define I2C1_PIN_SCL 27
#define DISPLAY_I2C_BLOCK i2c1
#define BUTTON_LAYOUT BUTTON_LAYOUT_RAPIDBOX
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_RAPIDBOXB
#define SPLASH_MODE SPLASH_MODE_STATIC
#define SPLASH_DURATION 2000

#define PSPASSTHROUGH_ENABLED 1
#define PSPASSTHROUGH_PIN_DPLUS 16

#define ANALOG_KEY_ENABLED 1
#define MUX_PIN 29
#define MUX_SELECTOR_PINS { 4, 5, 3, 2 }
#define TRAVEL_DISTANCE_IN_0_01MM 400
#define BOTTOM_MAGNETIC_POLE 0
#define ANALOG_KEY_ACTUATION_MODE 1
#define ANALOG_KEY_ACTUATION_POINT 150
#define ANALOG_KEY_PRESS_SENSITIVITY 20
#define ANALOG_KEY_RELEASE_SENSITIVITY 55

#define MUX_PIN_00 MuxAction::MUX_PIN_LEFT
#define MUX_PIN_01 MuxAction::MUX_PIN_DOWN
#define MUX_PIN_02 MuxAction::MUX_PIN_R2
#define MUX_PIN_03 MuxAction::MUX_PIN_B2
#define MUX_PIN_04 MuxAction::MUX_PIN_L3
#define MUX_PIN_05 MuxAction::MUX_PIN_B1
#define MUX_PIN_06 MuxAction::MUX_PIN_UP
#define MUX_PIN_07 MuxAction::MUX_PIN_RIGHT
#define MUX_PIN_08 MuxAction::MUX_PIN_NONE
#define MUX_PIN_09 MuxAction::MUX_PIN_NONE
#define MUX_PIN_10 MuxAction::MUX_PIN_L2
#define MUX_PIN_11 MuxAction::MUX_PIN_B3
#define MUX_PIN_12 MuxAction::MUX_PIN_L1
#define MUX_PIN_13 MuxAction::MUX_PIN_R1
#define MUX_PIN_14 MuxAction::MUX_PIN_B4
#define MUX_PIN_15 MuxAction::MUX_PIN_R3

#define DEFAULT_SPLASH \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0xFC,0x00,0x03,0x00,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x00, \
0x00,0x00,0x3F,0xFF,0x7F,0xC7,0xFF,0xFF,0x83,0xFC,0x7F,0xF0,0x0F,0x9F,0xFF,0x00, \
0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xC0, \
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0, \
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0, \
0x00,0x07,0xE0,0x01,0xF8,0xFF,0x00,0x71,0xFE,0x07,0xC0,0x1F,0xF0,0xF0,0xE1,0xF8, \
0x00,0x07,0x80,0x00,0xF0,0xE0,0x00,0x30,0x70,0x02,0x00,0x07,0xC0,0x70,0xC0,0xF8, \
0x00,0x07,0x80,0x30,0xC0,0xE0,0x00,0x20,0x00,0x00,0x00,0x03,0x00,0x70,0x00,0x78, \
0x00,0x07,0xC3,0xF0,0xC0,0xE0,0xFE,0x20,0x80,0x20,0x07,0xC2,0x00,0x30,0x00,0xF8, \
0x00,0x0F,0x83,0x81,0x80,0xE0,0xF0,0x40,0x81,0xE1,0x07,0x84,0x0C,0x18,0x01,0xF8, \
0x00,0x0F,0x80,0x02,0x01,0xE0,0x00,0x01,0x03,0xC2,0x0C,0x00,0x1C,0x18,0x03,0xF0, \
0x00,0x1F,0x00,0x06,0x01,0xC0,0x01,0x82,0x07,0x02,0x00,0x08,0x3C,0x38,0x07,0xE0, \
0x00,0x3E,0x00,0x7C,0x31,0xC0,0x0F,0x06,0x0E,0x04,0x00,0x10,0x78,0x38,0x0F,0xC0, \
0x00,0x3C,0x03,0xF0,0x61,0x80,0xFF,0x04,0x18,0x1C,0x00,0x60,0x78,0x60,0x3F,0x80, \
0x00,0x7C,0x00,0xF0,0x41,0x87,0xFE,0x08,0x30,0x38,0x00,0x20,0x70,0x60,0x3F,0x00, \
0x00,0xF8,0x20,0x60,0x01,0x07,0xFE,0x10,0x40,0xF0,0x7C,0x20,0x60,0xC0,0x1E,0x00, \
0x00,0xF8,0x70,0x00,0x00,0x0F,0xFC,0x30,0x01,0xF0,0xF8,0x20,0x00,0x80,0x1E,0x00, \
0x01,0xF0,0xFC,0x00,0x00,0x1F,0xF8,0x20,0x07,0xE0,0x80,0x60,0x01,0x03,0x1E,0x00, \
0x01,0xE0,0xFF,0x00,0x60,0x3F,0xF8,0x60,0x1F,0xC0,0x00,0x60,0x02,0x0F,0x1E,0x00, \
0x03,0xE1,0xFF,0x0F,0xE0,0x7F,0xF8,0xE0,0x7F,0xC0,0x00,0xE0,0x04,0x3F,0x9E,0x00, \
0x07,0xC3,0xFE,0x07,0xE0,0xFC,0xF3,0xE1,0xFF,0xC0,0x0F,0xF0,0x1C,0x7F,0x9E,0x00, \
0x07,0xC7,0xDF,0x77,0xF3,0xF8,0xF7,0xF7,0xFF,0xF1,0xFF,0xFC,0x3F,0xFF,0xFE,0x00, \
0x0F,0x8F,0x8F,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00, \
0x0F,0x1F,0x87,0xFF,0xFF,0xE0,0xFF,0xFF,0xDF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFC,0x00, \
0x0F,0x3E,0x03,0xFF,0xFF,0xC0,0x7F,0xFF,0x3F,0xFF,0xFC,0x1F,0xFF,0xC1,0xFC,0x00, \
0x0F,0xFC,0x01,0xFF,0xFE,0x00,0x7C,0x1E,0x3E,0x0F,0x00,0x03,0xFE,0x00,0x7C,0x00, \
0x0F,0xFC,0x00,0x0F,0x3C,0x00,0x78,0x00,0x78,0x00,0x00,0x00,0x70,0x00,0x3C,0x00, \
0x0F,0xF8,0x00,0x00,0x30,0x00,0x60,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x1C,0x00, \
0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00, \
0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

#endif
