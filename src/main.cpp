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
#include "my_servo.h"
#include "servo_handler.h"

bool load_config(const String& json);


shift_register_in_handler *shiftRegisterInHandler;
void setup() {
    Serial.begin(9600);
    bool config_successful = false;
    String json;
    while (!config_successful) {
        while (Serial.available() == 0){
            Serial.print("{\"CONFIG_FILE_NEEDED\": 9999}\n");
            delay(100);
        }     //wait for data available
        json = Serial.readStringUntil('\n');
        json.trim();
        config_successful = load_config(json);
    }

    serial_communication_handler::getInstance();
    sensor_handler::getInstance()->run();
    serial_in_command_handler::getInstance()->run();


    uint8_t a[]{0, 0};
    shift_register_out_handler::getInstance()->setDat(a);

}
void loop() {
}

bool load_config(const String& json){
    DynamicJsonDocument doc(4096);
    DeserializationError root = deserializeJson(doc, json.c_str());
    Serial.println(root.c_str());

    sensor_handler::getInstance();
    JsonObject sensors_root = doc["sensors"].as<JsonObject>();
    for(JsonPair keyValue : sensors_root){
        const String sen_name = keyValue.key().c_str();
        const String sen_type = doc["sensors"][keyValue.key().c_str()]["type"];
        if(sen_type == "digital")
            continue;
        const int sen_pin = doc["sensors"][keyValue.key().c_str()]["pin"];
        if(sen_type == "dht11")
            sensor_handler::getInstance()->add_sensor(sen_name, new DHT11_sensor(sen_pin, sen_name));
        else if(doc["sensors"][keyValue.key().c_str()]["type"] == "raw_analog")
            sensor_handler::getInstance()->add_sensor(sen_name, new raw_analog_sensor(sen_pin, sen_name));

    }

    JsonObject servos_root = doc["servo"].as<JsonObject>();
    for(JsonPair keyValue : servos_root) {
        const String ser_name = keyValue.key().c_str();
        const int ser_pin = doc["servo"][keyValue.key().c_str()]["pin"];
        servo_handler::getInstance()->add_servo(ser_name, new my_servo(ser_pin));
    }

    JsonObject shift_in_root = doc["shift_register_in"].as<JsonObject>();
    shiftRegisterInHandler = new shift_register_in_handler(shift_in_root["latch"], shift_in_root["data"], shift_in_root["clock"], shift_in_root["shift_reg_num"]);

    JsonObject shift_out_root = doc["shift_register_out"].as<JsonObject>();
    shift_register_out_handler::getInstance()->setUp(shift_out_root["latch"], shift_out_root["data"], shift_out_root["clock"], shift_out_root["shift_reg_num"]);
//    shiftRegisterOutHandler = new shift_register_out_handler(shift_out_root["latch"], shift_out_root["data"], shift_out_root["clock"], shift_out_root["shift_reg_num"]);

    return true;
}
