//
// Created by Pánczél Bence on 2023. 03. 25..
//


#include "sensor.h"
#include <cstdint>
#include "raw_analog_sensor.h"
#include "serial_communication_handler.h"


raw_analog_sensor::raw_analog_sensor(uint8_t sensor_pin, String sensor_name): sensor(sensor_pin, sensor_name) {
    pinMode(sensor_pin, INPUT);
}

void raw_analog_sensor::read_sensor() {
    float reading = analogRead(sensor_pin);
    String out = R"({ "SENSOR_DATA_FROM_ESP32": { ")" + this->sensor_name + R"(": {"raw_reading": )" + reading + " }}}\n";
    serial_communication_handler::getInstance()->send_sensor_data(this->sensor_name, out);

}
