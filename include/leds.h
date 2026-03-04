/**
 * Copyright 2025 Richard Kosegi
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <Arduino.h>
#include "consts.h"
#include "defs.h"

#define MCP23017_ORA_PORT   1
#define MCP23017_RED_PORT   0

#define LED_PWM_CHANNEL     0
#define LED_PWM_FREQ        4000
#define LED_PWM_BITS        8
#define LED_PWM_PIN         27
#define LED_EN_PIN          26

#define LED_PERCENT_2_DUTY(p)   (((1 << LED_PWM_BITS) * p) / 100)
#define LED_DUTY_2_PERCENT(d)   (d * 100 / (1 << LED_PWM_BITS))

void blinky_leds_init();
void blinky_leds_set_ora(uint8_t val);
void blinky_leds_set_red(uint8_t val);
void blinky_leds_clear();
void blinky_leds_seq(const struct seq_t *seq);
void blinky_leds_set_dim_level(uint8_t percent);
void blinky_leds_power_ctl(uint8_t power);

uint8_t blinky_leds_get_dim_level();
uint8_t blinky_leds_get_ora();
uint8_t blinky_leds_get_red();
