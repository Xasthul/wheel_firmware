#include <Arduino.h>
#include "bluetooth_connection_callbacks.h"

void BluetoothConnectionCallbacks::onConnect(BLEServer *pServer)
{
    Serial.println("Connected");
}
void BluetoothConnectionCallbacks::onDisconnect(BLEServer *pServer)
{
    Serial.println("Disconnected");
}
