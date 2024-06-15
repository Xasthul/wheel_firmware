#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bluetooth_core/bluetooth_core.h"

void setup()
{
  Serial.begin(115200);
  BluetoothCore *bluetoothCore = new BluetoothCore;

  bluetoothCore->initialize();
}

void loop()
{
  // delay(2000);
}