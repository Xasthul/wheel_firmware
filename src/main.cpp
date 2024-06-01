#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bluetooth/bluetooth.h"

void setup()
{
  Serial.begin(115200);
  BluetoothCore bluetoothCore;

  Serial.println("Starting BLE work!");
  bluetoothCore.initialize();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop()
{
  // delay(2000);
}