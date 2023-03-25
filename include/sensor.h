//
// Created by Pánczél Bence on 2023. 03. 05..
//

#ifndef SMARTHOME_SENSOR_H
#define SMARTHOME_SENSOR_H

#include "../lib/DHT/DHT.h"

class sensor {
protected:
    String sensor_name;
    uint8_t sensor_pin;
    sensor(uint8_t sensor_pin, String sensor_name): sensor_pin(sensor_pin), sensor_name(sensor_name){}
public:
    virtual void read_sensor()= 0;
};

#endif //SMARTHOME_SENSOR_H
