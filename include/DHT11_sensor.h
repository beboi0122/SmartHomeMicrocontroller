//
// Created by Pánczél Bence on 2023. 03. 05..
//

#ifndef SMARTHOME_DHT11_SENSOR_H
#define SMARTHOME_DHT11_SENSOR_H

class DHT11_sensor: public sensor {
private:
    DHT* dht;
public:
    DHT11_sensor(uint8_t sensor_pin, String sensor_name);
    void read_sensor() override;
};

#endif //SMARTHOME_DHT11_SENSOR_H
