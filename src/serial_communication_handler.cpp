//
// Created by Pánczél Bence on 2023. 03. 07..
//


#include "serial_communication_handler.h"

#include <utility>


serial_communication_handler* serial_communication_handler::instance = nullptr;

serial_communication_handler::serial_communication_handler() {
    sensor_data_row = new std::vector<const String*>();
    interrupt_data_row = new std::vector<String>();
    Serial.begin(9600);
    serial_print_thread = std::thread(&serial_communication_handler::print_to_serial, this);
    serial_print_thread.detach();
}

serial_communication_handler *serial_communication_handler::getInstance() {
    if(!instance)
        instance = new serial_communication_handler();
    return instance;
}

void serial_communication_handler::send_sensor_data(const String& sensor_name, const String& json) {
    this->sensor_data_lock.lock();
    sensor_data_row->push_back(new const String[2]{sensor_name, json});
    this->sensor_data_lock.unlock();
}

void serial_communication_handler::send_interrupt(const String& json) {
    this->interrupt_data_lock.lock();
    interrupt_data_row->push_back(json);
    this->interrupt_data_lock.unlock();
}


void serial_communication_handler::print_to_serial() {
    while(true){
        if(!interrupt_data_row->empty()){
            this->interrupt_data_lock.lock();
            for(const auto & i : *interrupt_data_row){
//                Serial.print("INERRUPT_FROM_ESP32\n");
//                Serial.print(String(i.length()) + "\n");
                Serial.print(i);
            }
            interrupt_data_row->clear();
            this->interrupt_data_lock.unlock();
        }
        this->sensor_data_lock.lock();
        for(const auto & i : *sensor_data_row){
//            Serial.print("SENSOR_DATA_FROM_ESP32\n");
//            //Serial.println(i[0]);
//            Serial.print(String(i[1].length()) + "\n");
//            Serial.print(i[1] + "\n");
            Serial.print(i[1]);
        }
        sensor_data_row->clear();
        this->sensor_data_lock.unlock();
        delay(100);
    }

}

