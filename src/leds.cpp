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
#include "MCP23017.h"

static MCP23017 mcp(MCP23017_ADDR);


uint8_t blinky_leds_get_dim_level() {
    return LED_DUTY_2_PERCENT(ledcRead(LED_PWM_CHANNEL));
}

void blinky_leds_set_dim_level(uint8_t percent) {
    if (percent > 100) {
        percent = 100;
    }
    ledcWrite(LED_PWM_CHANNEL, LED_PERCENT_2_DUTY(percent));
}

void blinky_leds_init()
{
    pinMode(LED_EN_PIN, OUTPUT);
    blinky_leds_power_ctl(LOW);

    ledcSetup(LED_PWM_CHANNEL, LED_PWM_FREQ , LED_PWM_BITS);
    ledcAttachPin(LED_PWM_PIN, LED_PWM_CHANNEL);
    blinky_leds_set_dim_level(LOW);

    mcp.begin(false);
    // all 16 bits are outputs
    mcp.pinMode16(0);

}

uint8_t blinky_leds_get_ora()
{
    return (uint8_t) (0xff & mcp.read8(MCP23017_ORA_PORT));
}

void blinky_leds_set_ora(uint8_t val)
{
    mcp.write8(MCP23017_ORA_PORT, val);
}

uint8_t blinky_leds_get_red()
{
    return (uint8_t) (0xff & mcp.read8(MCP23017_RED_PORT));
}

void blinky_leds_set_red(uint8_t val)
{
    mcp.write8(MCP23017_RED_PORT, val);
}

void blinky_leds_clear()
{
    mcp.write16(0);
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

void blinky_leds_power_ctl(uint8_t power)
{
    digitalWrite(LED_EN_PIN, power & 1);
}
