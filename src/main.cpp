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

#include "bt.h"
#include "buttons.h"
#include "consts.h"
#include "defs.h"
#include "leds.h"

// globals

const extern struct seq_t *blinky_seq_all_red_seqs[];
const extern struct seq_t *blinky_seq_ora_left_seq;
const extern struct seq_t *blinky_seq_ora_right_seq;
const extern int blinky_seq_all_red_seqs_count;

// for debounce
volatile unsigned long btn1_last_press = 0;

volatile uint8_t mode = BLINKY_MODE_NONE;
volatile uint8_t lastMode = BLINKY_MODE_NONE;
volatile boolean running = true;

static void blinky_main_mode_set_and_save(uint8_t newMode)
{
    lastMode = mode;
    mode = newMode;
}

static void blinky_main_mode_restore()
{
    mode = lastMode;
    lastMode = BLINKY_MODE_NONE;
}

static void blinky_main_init()
{
    mode = BLINKY_MODE_NONE;
    lastMode = BLINKY_MODE_NONE;
}

// ISR

void ARDUINO_ISR_ATTR btn1_isr()
{
    unsigned long now = millis();
    if ((now - btn1_last_press) > BTN_DEBOUNCE_MILLIS)
    {
        btn1_last_press = now;
        uint8_t m = mode;
        m++;
        if (m > blinky_seq_all_red_seqs_count)
        {
            mode = BLINKY_MODE_NONE;
        }
        mode = m;
    }
}

class ModeBleCharacteristicCallback : public BLECharacteristicCallbacks
{
public:
    void onRead(BLECharacteristic *pChar)
    {
        pChar->setValue((uint8_t*)&mode, 1);
    }

    void onWrite(BLECharacteristic *pChar)
    {
        running = true;
        const auto val = pChar->getValue();
        uint8_t newMode = (uint8_t)val.data()[0];
        blinky_main_mode_set_and_save(newMode);
    }
};

class LedBitsBleCharacteristicCallback : public BLECharacteristicCallbacks
{
public:
    void onRead(BLECharacteristic *pChar)
    {
        uint8_t data[2] = {0};
        data[0] = blinky_leds_get_ora();
        data[1] = blinky_leds_get_red();
        pChar->setValue(data, sizeof(data));
    }

    void onWrite(BLECharacteristic *pChar)
    {
        running = false;
        const auto val = pChar->getValue();
        if (val.size() < 2)
        {
            return;
        }
        blinky_leds_set_ora(val.data()[0]);
        blinky_leds_set_red(val.data()[1]);
    }
};

BLECharacteristicCallbacks *modeCb = new ModeBleCharacteristicCallback();
BLECharacteristicCallbacks *ledCb = new LedBitsBleCharacteristicCallback();

void setup()
{
    Serial.begin(115200);

    blinky_leds_init();
    blinky_buttons_init(btn1_isr);
    blinky_bt_init(modeCb, ledCb);

    Serial.println("BLE configured");

    blinky_main_init();

    Serial.println("Setup done");
}

void loop()
{
    if (running)
    {
        if (mode == BLINKY_MODE_NONE)
        {
            blinky_leds_clear();
            delay(500);
        }
        else if (mode >= RED_MODE_START && mode <= RED_MODE_END)
        {
            blinky_leds_seq(blinky_seq_all_red_seqs[mode - RED_MODE_START]);
        }
        else if (mode == ORA_MODE_LEFT)
        {
            blinky_leds_seq(blinky_seq_ora_left_seq);
        }
        else if (mode == ORA_MODE_RIGHT)
        {
            blinky_leds_seq(blinky_seq_ora_right_seq);
        }
        else
        {
            delay(250);
        }
    } else
    {
        delay(100);
    }
}
