#include <Arduino.h>
#include <Bluepad32.h>
#include "Helpers.hpp"
#include "GamePadInput.hpp"
#include "Mole.hpp"
#include "ProximitySensor.hpp"

ControllerPtr myController = nullptr;
Mole mole;
ProximitySensor lidar;
unsigned long moleTimer = 0;


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
        mole.emergencyStop();
        return;
    }
    Serial.println("ERROR: Unknown Controller disconnected. This should NOT display.");
}


void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    mole.begin();
    lidar.begin();

    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());

    // const uint8_t* addr = BP32.localBdAddress();
    // Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);


    BP32.setup(&onConnectedController, &onDisconnectedController);
    
    // forget device on every boot: 
    // BP32.forgetBluetoothKeys();
}

void loop()
{
    unsigned long now = millis();
    bool dataUpdated = BP32.update(); 

    if (myController == nullptr or !myController->isConnected()) {
        return;
    }

    lidar.updateData();
    Serial.printf("Distance: %d cm", lidar.getDistance());
    Serial.println();

    mole.tick(myController, now);
    mole.printData();

    delay(1);
}


// #include <Arduino.h>

// #define RXD2 35 // Podłącz do Pin 3 (TXD) w TF-Luna
// #define TXD2 17 // Podłącz do Pin 2 (RXD) w TF-Luna

// void setup() {
//   Serial.begin(115200); // Monitor portu szeregowego (USB)
  
//   // Inicjalizacja sprzętowego portu UART2 na pinach 16 i 17
//   Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
//   Serial.println("Start odczytu TF-Luna na ESP32 (UART2)...");
// }

// void loop() {
//   // Czujnik wysyła 9-bajtowe ramki danych zaczynające się od 0x59 0x59
//   if (Serial2.available() >= 9) {
//     if (Serial2.read() == 0x59) {
//       if (Serial2.read() == 0x59) {
//         uint8_t buf[7];
//         Serial2.readBytes(buf, 7);

//         // Weryfikacja sumy kontrolnej
//         uint8_t checksum = 0x59 + 0x59;
//         for (int i = 0; i < 6; i++) {
//           checksum += buf[i];
//         }

//         if (checksum == buf[6]) {
//           int16_t distance = buf[0] | (buf[1] << 8);
//           uint16_t amplitude = buf[2] | (buf[3] << 8);
//           float temperature = ((buf[4] | (buf[5] << 8)) / 8.0) - 256.0;

//           Serial.printf("Odleglosc: %d cm | Sygnal: %u | Temp: %.1f C\n", 
//                         distance, amplitude, temperature);
//         }
//       }
//     }
//   }
//   delay(10);
// }