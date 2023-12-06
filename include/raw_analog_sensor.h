//
// Created by Pánczél Bence on 2023. 03. 25..
//

#ifndef SMARTHOME_RAW_ANALOG_SENSOR_H
#define SMARTHOME_RAW_ANALOG_SENSOR_H


class raw_analog_sensor: public sensor {
public:
    raw_analog_sensor(uint8_t sensor_pin, String sensor_name);
    float last_sent = -1000;
    void read_sensor() override;

};


#endif //SMARTHOME_RAW_ANALOG_SENSOR_H
