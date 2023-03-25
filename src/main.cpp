#include <Arduino.h>
#include <map>
#include "sensor.h"
#include "DHT11_sensor.h"
#include "serial_communication_handler.h"
#include "shift_register_out_handler.h"
#include "raw_analog_sensor.h"
#include "sensor_handler.h"
shift_register_out_handler* shiftRegisterOutHandler;
void setup() {
    serial_communication_handler::getInstance();
    sensor_handler* h = sensor_handler::getInstance();
    h->add_sensor("room1_dht11", new DHT11_sensor(23, "room1_dht11"));
    h->add_sensor("garden_light", new raw_analog_sensor(35, "garden_light"));
    h->run();

    pinMode(2, OUTPUT);

    shiftRegisterOutHandler = new shift_register_out_handler(33, 25, 32);
    shiftRegisterOutHandler->setDat(255);
    //delay(3000);
}
void loop() {
    digitalWrite(2, LOW);
    for(int i = 0; i < 8; i++){
        shiftRegisterOutHandler->flipPin(i);
        delay(100);
    }
    digitalWrite(2, HIGH);
    delay(500);
}