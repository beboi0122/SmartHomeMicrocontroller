#include <Arduino.h>
#include <map>
#include "sensor.h"
#include "DHT11_sensor.h"
#include "serial_communication_handler.h"
#include "shift_register_out_handler.h"
#include "raw_analog_sensor.h"
#include "sensor_handler.h"
#include "../lib/ArduinoJson.h"
#include "shift_register_in_handler.h"

bool load_config(const String& json);

shift_register_out_handler* shiftRegisterOutHandler;
shift_register_in_handler *shiftRegisterInHandler;
void setup() {
    Serial.begin(9600);
    bool config_successful = false;
    String json;
    while (!config_successful) {
        while (Serial.available() == 0);     //wait for data available
        json = Serial.readStringUntil('\n');
        json.trim();
        config_successful = load_config(json);
    }

    serial_communication_handler::getInstance();
    sensor_handler::getInstance();
    sensor_handler::getInstance()->add_sensor("room1_dht11", new DHT11_sensor(23, "room1_dht11"));
    sensor_handler::getInstance()->add_sensor("garden_light", new raw_analog_sensor(35, "garden_light"));
//    sensor_handler::getInstance()->run();

    pinMode(2, OUTPUT);
//    shiftRegisterInHandler = new shift_register_in_handler("shift1", 26, 35, 27, 2);
    shiftRegisterOutHandler = new shift_register_out_handler(33, 25, 32, 2);
    uint8_t a[]{0, 0};
    shiftRegisterOutHandler->setDat(a);
}
void loop() {
    for(int i = 0; i < 16; i++){
        shiftRegisterOutHandler->flipPin(i);
        delay(100);
    }
    for(int i = 16; i >= 0; i--){
        shiftRegisterOutHandler->flipPin(i);
        delay(100);
    }
}

bool load_config(const String& json){
    DynamicJsonDocument doc(1024);
    DeserializationError root = deserializeJson(doc, json.c_str());
    Serial.println(root.c_str());
    int sensor_num = doc["sensors"].size();
    Serial.println(sensor_num);

    JsonObject sensors_root = doc["sensors"].as<JsonObject>();
    for(JsonPair keyValue : sensors_root){
        if(doc["sensors"][keyValue.key().c_str()]["type"] == "dht11")
            Serial.print("true\n");
        else
            Serial.print("fales\n");
        delay(50);
    }
//    Serial.println(sensors_root);

    return true;
}
