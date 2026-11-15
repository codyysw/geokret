#include <Arduino.h>
#include <Bluepad32.h>
#include <AccelStepper.h>
#include "Helpers.hpp"
#include "GamePadInput.hpp"
#include "Mole.hpp"
#include "ProximitySensor.hpp"

ControllerPtr myController = nullptr;
Mole mole;

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

    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());

    // const uint8_t* addr = BP32.localBdAddress();
    // Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);


    BP32.setup(&onConnectedController, &onDisconnectedController);
    
    // forget device on every boot: 
    // BP32.forgetBluetoothKeys();
}

void loop()
{
    BP32.update();

    mole.tick(myController);
}

// !! ---- MYLIDAR TEST

// #include <Arduino.h>
// #include "ProximitySensor.hpp"

// ProximitySensor lidar;
// void setup() {
//     Serial.begin(115200);
//     lidar.begin();
// }



// void loop() {
//     lidar.updateData();
//     Serial.printf("Dist: %d ; Signal: %d\n", lidar.getDistance(), lidar.getSignal());
//     delay(10);
// }

// ! --- ACCELSTEPPER TEST

// #include <Arduino.h>
// #include <AccelStepper.h>
// #include "Config.hpp"

// AccelStepper testStepper(
//     AccelStepper::FULL4WIRE, 
//     Pins::ROTATION_TOWER.IN1,
//     Pins::ROTATION_TOWER.IN3,
//     Pins::ROTATION_TOWER.IN2,
//     Pins::ROTATION_TOWER.IN4
// );

// int STEPS_PER_ROTATION = 2048;

// void setup() {
//     Serial.begin(115200);
//     testStepper.setMaxSpeed(512.0);
//     testStepper.setAcceleration(500.0);
//     delay(5000);
//     testStepper.moveTo(180*STEPS_PER_ROTATION);
// }


// void loop() {
//     testStepper.run();
// }

// ! ---- MYSTEPPER TEST

// #include <Arduino.h>
// #include "StepperMotor.hpp"
// #include "Config.hpp"

// StepperMotor myStepper{Pins::ROTATION_TOWER};


// void setup() {
//     Serial.begin(115200);
//     myStepper.begin();
//     delay(2000);
//     //myStepper.moveTo(-(StepperMotor::STEPS_PER_ROTATION / 2));
// }

// int a = 1;
// void loop() {
//     if (myStepper.distanceToGo() == 0) {
//         myStepper.move(a * StepperMotor::STEPS_PER_ROTATION / 2);
//         a = -a;
//     }
//     myStepper.run();
// }