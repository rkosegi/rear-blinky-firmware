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

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#pragma pack(push, 1)
struct seq_t {
    uint8_t type;           // 0 - channel_0 (red) , 1 - channel_1 (orange)
    uint8_t len;            // total length of everything
    uint16_t step_wait;     // how long to wait between steps, in milliseconds
    uint16_t seq_wait;      // how long to wait at the end of sequence
    uint8_t count;          // number of steps in this sequence
    uint8_t *steps;         // actual step - bit pattern to apply to LED IO channel
};
#pragma pack(pop)
