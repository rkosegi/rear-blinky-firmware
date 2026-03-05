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

#include <Arduino.h>
#include "leds.h"

static uint8_t ora_right_steps[] = {
    ORA_C2_MASK | ORA_1_MASK,
    ORA_C3_MASK | ORA_2_MASK,
    ORA_C4_MASK | ORA_3_MASK,
};

static uint8_t ora_left_steps[] = {
    ORA_C3_MASK | ORA_3_MASK,
    ORA_C2_MASK | ORA_2_MASK,
    ORA_C1_MASK | ORA_1_MASK,
};

static uint8_t blink_red1_steps[] = {
    RED_L_MASK | RED_R_MASK,
    RED_C_MASK
};

static uint8_t blink_red2_steps[] = {
    RED_L_MASK,
    RED_R_MASK,
    RED_L_MASK,
    RED_R_MASK,
    RED_C_MASK | RED_L_MASK | RED_R_MASK,
    0,
    RED_C_MASK,
};

static uint8_t blink_red3_steps[] = {
    RED_L_MASK,
    RED_C_MASK,
    0,
    0,
    0,
    RED_R_MASK,
    RED_C_MASK,
    0,
    0,
    0,
    RED_L_MASK | RED_R_MASK | RED_C_MASK,
    0
};

static uint8_t blink_red4_steps[] = {
    RED_L_MASK | RED_C_MASK,
    0,
    RED_L_MASK | RED_C_MASK,
    0,
    0,
    0,
    RED_R_MASK | RED_C_MASK,
    0,
    RED_R_MASK | RED_C_MASK,
    0,
    0,
    0,
    0,
    0
};

static uint8_t blink_red5_steps[] = {
    RED_L_MASK,
    RED_C_MASK,
    RED_R_MASK,
    RED_R_MASK,
    RED_C_MASK,
    RED_L_MASK
};

struct seq_t turn_left_seq = {
    .type       =   SEQ_TYPE_ORA,
    .len        =   0,
    .step_wait  =   100,
    .seq_wait   =   500,
    .count      =   sizeof(ora_left_steps),
    .steps      =   (uint8_t *)&ora_left_steps,
};

struct seq_t turn_right_seq = {
    .type       =   SEQ_TYPE_ORA,
    .len        =   0,
    .step_wait  =   100,
    .seq_wait   =   500,
    .count      =   sizeof(ora_right_steps),
    .steps      =   (uint8_t *)&ora_right_steps,
};

struct seq_t blink_red1_seq = {
    .type       =   SEQ_TYPE_RED,
    .len        =   0,
    .step_wait  =   250,
    .seq_wait   =   100,
    .count      =   sizeof(blink_red1_steps),
    .steps      =   (uint8_t *)&blink_red1_steps,
};

struct seq_t blink_red2_seq = {
    .type       =   SEQ_TYPE_RED,
    .len        =   0,
    .step_wait  =   50,
    .seq_wait   =   20,
    .count      =   sizeof(blink_red2_steps),
    .steps      =   (uint8_t *)&blink_red2_steps,
};

struct seq_t blink_red3_seq = {
    .type       =   SEQ_TYPE_RED,
    .len        =   0,
    .step_wait  =   30,
    .seq_wait   =   2000,
    .count      =   sizeof(blink_red3_steps),
    .steps      =   (uint8_t *)&blink_red3_steps,
};

struct seq_t blink_red4_seq = {
    .type       =   SEQ_TYPE_RED,
    .len        =   0,
    .step_wait  = 30,
    .seq_wait   = 50,
    .count      = sizeof(blink_red4_steps),
    .steps      = (uint8_t *)&blink_red4_steps,
};

struct seq_t blink_red5_seq = {
    .type       =   SEQ_TYPE_RED,
    .len        =   0,
    .step_wait  = 300,
    .seq_wait   = 300,
    .count      = sizeof(blink_red5_steps),
    .steps      = (uint8_t *)&blink_red5_steps,
};

const struct seq_t *blinky_seq_ora_left_seq = &turn_left_seq;
const struct seq_t *blinky_seq_ora_right_seq = &turn_right_seq;
const struct seq_t *blinky_seq_all_red_seqs[] = {
    &blink_red1_seq,
    &blink_red2_seq,
    &blink_red3_seq,
    &blink_red4_seq,
    &blink_red5_seq,
};

const extern int blinky_seq_all_red_seqs_count = sizeof(blinky_seq_all_red_seqs) / sizeof(struct seq_t *);
