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

#define BLINKY_MODE_NONE        0

#define BTN_1_PIN               GPIO_NUM_15

#define CTL_ORA_C1              GPIO_NUM_16
#define CTL_ORA_C2              GPIO_NUM_17
#define CTL_ORA_C3              GPIO_NUM_18
#define CTL_ORA_C4              GPIO_NUM_19

#define CTL_ORA_1               GPIO_NUM_25
#define CTL_ORA_2               GPIO_NUM_26
#define CTL_ORA_3               GPIO_NUM_27

#define CTL_RED_L               GPIO_NUM_21
#define CTL_RED_C               GPIO_NUM_22
#define CTL_RED_R               GPIO_NUM_23

#define BTN_DEBOUNCE_MILLIS     200ul

#define ORA_C1_BIT              0
#define ORA_C2_BIT              1
#define ORA_C3_BIT              2
#define ORA_C4_BIT              3
#define ORA_1_BIT               4
#define ORA_2_BIT               5
#define ORA_3_BIT               6

#define ORA_C1_MASK             1 << ORA_C1_BIT
#define ORA_C2_MASK             1 << ORA_C2_BIT
#define ORA_C3_MASK             1 << ORA_C3_BIT
#define ORA_C4_MASK             1 << ORA_C4_BIT
#define ORA_1_MASK              1 << ORA_1_BIT
#define ORA_2_MASK              1 << ORA_2_BIT
#define ORA_3_MASK              1 << ORA_3_BIT

#define RED_L_BIT               0
#define RED_C_BIT               1
#define RED_R_BIT               2

#define RED_L_MASK              1 << RED_L_BIT
#define RED_C_MASK              1 << RED_C_BIT
#define RED_R_MASK              1 << RED_R_BIT

#define RED_MODE_START          1
#define RED_MODE_END            RED_MODE_START + 5
#define ORA_MODE_LEFT           11
#define ORA_MODE_RIGHT          12
