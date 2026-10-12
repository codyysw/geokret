#include <Arduino.h>
#include <Bluepad32.h>
#include "Helpers.hpp"
#include "GamePadInput.hpp"
#include "Mole.hpp"


ControllerPtr myController = nullptr;
Mole mole;
constexpr int DELAY = 25;

void onConnectedController(ControllerPtr ctl) 
{
    if (myController != nullptr) {
        Serial.printf("ERROR: There is an already connected Controller.");
        return;
    }

    myController = ctl;
    Serial.printf("CALLBACK: Controller is connected");
    digitalWrite(LED_BUILTIN,HIGH);
    ControllerProperties properties = myController->getProperties();
    Serial.printf(
        "Controller model: %s, VID=0x%04x, PID=0x%04x\n", 
        myController->getModelName().c_str(), 
        properties.vendor_id, properties.product_id
    );
}

void onDisconnectedController(ControllerPtr ctl) 
{
    if (myController == ctl) {
        Serial.printf("CALLBACK: Controller disconnected");
        myController = nullptr;
        digitalWrite(LED_BUILTIN,LOW);
        return;
    }
    Serial.println("ERROR: Unknown Controller disconnected. This should NOT display.");
}


void setup()
{
    pinMode(STDBY1, OUTPUT);
    digitalWrite(STDBY1, HIGH);

    pinMode(STDBY2, OUTPUT);
    digitalWrite(STDBY2, HIGH);

    pinMode(LED_BUILTIN, OUTPUT);
    mole.begin();
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());

    // const uint8_t* addr = BP32.localBdAddress();
    // Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);


    BP32.setup(&onConnectedController, &onDisconnectedController);
    
    // forget device on every boot: 
    // BP32.forgetBluetoothKeys();
}

void loop()
{
    bool dataUpdated = BP32.update(); 

    if (myController == nullptr or !myController->isConnected()) {
        return;
    }
    // Helpers::printPadInput(myController);
    mole.tick(myController);
    mole.printPadData();

    delay(DELAY);


}