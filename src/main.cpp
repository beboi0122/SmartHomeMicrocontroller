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
#include "serial_in_command_handler.h"

bool load_config(const String& json);

//shift_register_out_handler* shiftRegisterOutHandler;
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
//    sensor_handler::getInstance();
//    sensor_handler::getInstance()->add_sensor("room1_dht11", new DHT11_sensor(23, "room1_dht11"));
//    sensor_handler::getInstance()->add_sensor("garden_light", new raw_analog_sensor(35, "garden_light"));
    sensor_handler::getInstance()->run();
    serial_in_command_handler::getInstance()->run();


    pinMode(2, OUTPUT);
//    shiftRegisterInHandler = new shift_register_in_handler(26, 35, 27, 2);
//    shiftRegisterOutHandler = new shift_register_out_handler(33, 25, 32, 2);
    uint8_t a[]{0, 0};
//    shiftRegisterOutHandler->setDat(a);
    shift_register_out_handler::getInstance()->setDat(a);
}
void loop() {
//    for(int i = 0; i < 16; i++){
//        shift_register_out_handler::getInstance()->flipPin(i);
//        delay(100);
//    }
//    for(int i = 16; i >= 0; i--){
//        shift_register_out_handler::getInstance()->flipPin(i);
//        delay(100);
//    }
}

bool load_config(const String& json){
    DynamicJsonDocument doc(1024);
    DeserializationError root = deserializeJson(doc, json.c_str());
    Serial.println(root.c_str());

    sensor_handler::getInstance();
    JsonObject sensors_root = doc["sensors"].as<JsonObject>();
    for(JsonPair keyValue : sensors_root){
        const String sen_name = keyValue.key().c_str();
        const String sen_type = doc["sensors"][keyValue.key().c_str()]["type"];
        const int sen_pin = doc["sensors"][keyValue.key().c_str()]["pin"];
        if(sen_type == "dht11")
            sensor_handler::getInstance()->add_sensor(sen_name, new DHT11_sensor(sen_pin, sen_name));
        else if(doc["sensors"][keyValue.key().c_str()]["type"] == "raw_analog")
            sensor_handler::getInstance()->add_sensor(sen_name, new raw_analog_sensor(sen_pin, sen_name));

//        Serial.print(sen_name + "\n");
//        Serial.print(sen_type + "\n");
//        Serial.print(String(sen_pin) + "\n");
//        delay(50);
    }

    JsonObject shift_in_root = doc["shift_register_in"].as<JsonObject>();
    shiftRegisterInHandler = new shift_register_in_handler(shift_in_root["latch"], shift_in_root["data"], shift_in_root["clock"], shift_in_root["shift_reg_num"]);

    JsonObject shift_out_root = doc["shift_register_out"].as<JsonObject>();
    shift_register_out_handler::getInstance()->setUp(shift_out_root["latch"], shift_out_root["data"], shift_out_root["clock"], shift_out_root["shift_reg_num"]);
//    shiftRegisterOutHandler = new shift_register_out_handler(shift_out_root["latch"], shift_out_root["data"], shift_out_root["clock"], shift_out_root["shift_reg_num"]);

    return true;
}
