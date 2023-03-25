//
// Created by Pánczél Bence on 2023. 03. 25..
//


#include "sensor.h"
#include <vector>
#include <thread>
#include <map>
#include "sensor_handler.h"

sensor_handler* sensor_handler::instance = nullptr;


sensor_handler::sensor_handler() {}

sensor_handler *sensor_handler::getInstance() {
    if(!instance)
        instance = new sensor_handler();
    return instance;
}

void sensor_handler::add_sensor(const String& sensor_name, sensor* sensor) {
    sensors.insert(std::make_pair(sensor_name, sensor));
    sensor_names.push_back(sensor_name);
}

void sensor_handler::run() {
    sensor_read_thread = std::thread(&sensor_handler::read_sensors, this);
    sensor_read_thread.detach();
}

void sensor_handler::read_sensors() {
    while(true){
        for(const String& name : sensor_names){
            sensors[name]->read_sensor();
        }
        delay(500);
    }
}


