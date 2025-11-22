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
#include <BLEDevice.h>
#include <BLEUUID.h>
#include "consts.h"

const static BLEUUID uuidDesc2901 = BLEUUID((uint16_t) 0x2901);

const static BLEUUID uuidBatteryService = BLEUUID((uint16_t) 0x180F);
const static BLEUUID uuidBatteryLevelChar = BLEUUID((uint16_t) 0x2A19);

const static BLEUUID uuidLedService = BLEUUID("27f65506-2524-4df3-803a-5f74e5a32ada");
const static BLEUUID uuidModeChar = BLEUUID("d5dc531e-0c9a-4cd9-a696-4bcb8c5be548");
const static BLEUUID uuidLedBitsChar = BLEUUID("1e0b46a6-7f06-4fc6-a66e-a054b158828d");

static BLEAdvertising *pBLEAdvertising;
static BLEService *pBLELedService;
static BLEService *pBLEBatteryService;

class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        Serial.println("BLE connected");
    }

    void onDisconnect(BLEServer* pServer) override {
        Serial.println("BLE disconnected, restarting advertising");
        BLEDevice::startAdvertising();
    }
};

void blinky_bt_init(BLECharacteristicCallbacks *modeCb, BLECharacteristicCallbacks *ledCb) {
    BLECharacteristic *pChar = NULL;
    BLEDescriptor *desc = NULL;

    BLEDevice::init("rear-blinky");
    BLEServer *pBLEServer = BLEDevice::createServer();

    // Battery service
    pBLEBatteryService = pBLEServer->createService(uuidBatteryService);
    pChar = pBLEBatteryService->createCharacteristic(uuidBatteryLevelChar, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    desc = new BLEDescriptor(uuidDesc2901);
    desc->setValue("Battery level");
    pChar->addDescriptor(desc);

    pBLEBatteryService->start();

    // LED service
    pBLELedService = pBLEServer->createService(uuidLedService);

    pChar = pBLELedService->createCharacteristic(uuidModeChar, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    desc = new BLEDescriptor(uuidDesc2901);
    desc->setValue("LED blinking mode");
    pChar->setCallbacks(modeCb);
    pChar->addDescriptor(desc);

    pChar = pBLELedService->createCharacteristic(uuidLedBitsChar, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    desc = new BLEDescriptor(uuidDesc2901);
    desc->setValue("LED bits pattern");
    pChar->setCallbacks(ledCb);
    pChar->addDescriptor(desc);

    pBLELedService->start();

    pBLEServer->setCallbacks(new ServerCallbacks());

    // Advertise services
    pBLEAdvertising = pBLEServer->getAdvertising();
    pBLEAdvertising->setScanResponse(false);
    pBLEAdvertising->setMinPreferred(0x00);
    pBLEAdvertising->addServiceUUID(uuidBatteryService);
    pBLEAdvertising->addServiceUUID(uuidLedService);
    pBLEAdvertising->start();
}

void blinky_bt_close() {
    if (pBLEAdvertising != NULL) {
        pBLEAdvertising->stop();
        pBLEAdvertising = NULL;
    }
    if (pBLELedService != NULL) {
        pBLELedService->stop();
        pBLELedService = NULL;
    }
    BLEDevice::deinit(true);
}
