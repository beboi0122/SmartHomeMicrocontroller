//
// Created by Pánczél Bence on 2023. 03. 07..
//

#ifndef SMARTHOME_SERIAL_COMMUNICATION_HANDLER_H
#define SMARTHOME_SERIAL_COMMUNICATION_HANDLER_H


#include <map>
#include <vector>
#include <iostream>
#include <mutex>
#include "sensor.h"
#include <thread>

class serial_communication_handler {
private:
    std::mutex sensor_data_lock;
    std::mutex interrupt_data_lock;
    std::vector<const String*>* sensor_data_row;
    std::vector<String>* interrupt_data_row;
    std::thread serial_print_thread;

    static serial_communication_handler* instance;
    serial_communication_handler();
    void print_to_serial();
public:
    serial_communication_handler(const serial_communication_handler& obj) = delete;
    static serial_communication_handler* getInstance();
    void send_sensor_data(const String& sensor_name, const String& json);
    void send_interrupt(const String& json);
};


#endif //SMARTHOME_SERIAL_COMMUNICATION_HANDLER_H
