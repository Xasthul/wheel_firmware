#include <BLEServer.h>

class BluetoothConnectionCallbacks : public BLEServerCallbacks
{
public:
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
};