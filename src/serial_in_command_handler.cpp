//
// Created by Pánczél Bence on 2023. 04. 02..
//

#include <Arduino.h>
#include <thread>
#include "serial_in_command_handler.h"
#include "../lib/ArduinoJson.h"
#include "shift_register_out_handler.h"

serial_in_command_handler* serial_in_command_handler::instance = nullptr;


serial_in_command_handler::serial_in_command_handler() = default;

void serial_in_command_handler::read_from_serial() {
    while(true) {
        while (Serial.available() == 0);     //wait for data available
        String json = Serial.readStringUntil('\n');
        json.trim();
        DynamicJsonDocument doc(256);
        DeserializationError root = deserializeJson(doc, json.c_str());
        if(root == root.Ok){
            JsonObject msg_root = doc.as<JsonObject>();
            for(JsonPair keyValue : msg_root){
                const String msg = keyValue.key().c_str();
                if(msg == "SHIFT_OUT_PIN_VAL"){
                    unsigned int pin = doc[msg]["pin"];
                    unsigned int val = doc[msg]["val"];
                    shift_register_out_handler::getInstance()->setPin(pin, val);
                }
            }
        }
    }
}

serial_in_command_handler *serial_in_command_handler::getInstance() {
    if(!instance)
        instance = new serial_in_command_handler();
    return instance;
}

void serial_in_command_handler::run() {
    serial_read_thread = std::thread(&serial_in_command_handler::read_from_serial, this);
    serial_read_thread.detach();
}
