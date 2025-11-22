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

#include "leds.h"

void blinky_leds_init()
{
    pinMode(CTL_RED_L, OUTPUT);
    pinMode(CTL_RED_C, OUTPUT);
    pinMode(CTL_RED_R, OUTPUT);

    pinMode(CTL_ORA_C1, OUTPUT);
    pinMode(CTL_ORA_C2, OUTPUT);
    pinMode(CTL_ORA_C3, OUTPUT);
    pinMode(CTL_ORA_C4, OUTPUT);

    pinMode(CTL_ORA_1, OUTPUT);
    pinMode(CTL_ORA_2, OUTPUT);
    pinMode(CTL_ORA_3, OUTPUT);
}

uint8_t blinky_leds_get_ora()
{
    uint8_t out = 0;
     out |= digitalRead(CTL_ORA_C1) << ORA_C1_BIT;
     out |= digitalRead(CTL_ORA_C2) << ORA_C2_BIT;
     out |= digitalRead(CTL_ORA_C3) << ORA_C3_BIT;
     out |= digitalRead(CTL_ORA_C4) << ORA_C4_BIT;

     out |= digitalRead(CTL_ORA_1) << ORA_1_BIT;
     out |= digitalRead(CTL_ORA_2) << ORA_2_BIT;
     out |= digitalRead(CTL_ORA_3) << ORA_3_BIT;
    return out;
}

void blinky_leds_set_ora(uint8_t val)
{
    digitalWrite(CTL_ORA_C1, (uint8_t)(val & ORA_C1_MASK));
    digitalWrite(CTL_ORA_C2, (uint8_t)(val & ORA_C2_MASK));
    digitalWrite(CTL_ORA_C3, (uint8_t)(val & ORA_C3_MASK));
    digitalWrite(CTL_ORA_C4, (uint8_t)(val & ORA_C4_MASK));

    digitalWrite(CTL_ORA_1, (uint8_t)(val & ORA_1_MASK));
    digitalWrite(CTL_ORA_2, (uint8_t)(val & ORA_2_MASK));
    digitalWrite(CTL_ORA_3, (uint8_t)(val & ORA_3_MASK));
}

uint8_t blinky_leds_get_red()
{
    uint8_t out = 0;
     out |= digitalRead(CTL_RED_L) << RED_L_BIT;
     out |= digitalRead(CTL_RED_C) << RED_C_BIT;
     out |= digitalRead(CTL_RED_R) << RED_R_BIT;
    return out;
}

void blinky_leds_set_red(uint8_t val)
{
    digitalWrite(CTL_RED_L, (uint8_t)(val & RED_L_MASK));
    digitalWrite(CTL_RED_C, (uint8_t)(val & RED_C_MASK));
    digitalWrite(CTL_RED_R, (uint8_t)(val & RED_R_MASK));
}

void blinky_leds_clear()
{
    blinky_leds_set_ora(0);
    blinky_leds_set_red(0);
}

void blinky_leds_seq(const struct seq_t *seq)
{
    for (int i = 0; i < seq->count; i++)
    {
        seq->apply_fn(seq->steps[i]);
        delay(seq->step_wait);
    }
    delay(seq->seq_wait);
    blinky_leds_clear();
}
