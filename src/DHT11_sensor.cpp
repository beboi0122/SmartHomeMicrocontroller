//
// Created by Pánczél Bence on 2023. 03. 05..
//
#include "sensor.h"
#include "DHT11_sensor.h"
#include "serial_communication_handler.h"

#include <utility>

DHT11_sensor::DHT11_sensor(uint8_t sensor_pin, String sensor_name): sensor(sensor_pin, std::move(sensor_name)) {
    this->dht = new DHT(sensor_pin, DHT11);
    dht->begin();
}

void DHT11_sensor::read_sensor() {
    float temp =  this->dht->readTemperature();
    float hum = this->dht->readHumidity();
    if(abs(last_sent_hum-hum)>3 or abs(last_sent_temp-temp)>0.5) {
        last_sent_temp = temp;
        last_sent_hum = hum;
        String out = R"({ "SENSOR_DATA_FROM_ESP32": { ")" + this->sensor_name + R"(": {"temperature": )" + temp +
                     R"(, "humidity": )" + hum + " }}}\n";


        serial_communication_handler::getInstance()->send_sensor_data(this->sensor_name, out);
    }

    /*String out_len = String(out.length()) + "\n";
    Serial.print("SENSOR_DATA_FROM_ESP32\n");
    Serial.print(out_len);
    //delay(5000);
    Serial.print(out);*/
}
