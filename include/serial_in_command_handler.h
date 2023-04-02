//
// Created by Pánczél Bence on 2023. 04. 02..
//

#ifndef SMARTHOMEARDUINO_SERIAL_IN_COMMAND_HANDLER_H
#define SMARTHOMEARDUINO_SERIAL_IN_COMMAND_HANDLER_H


class serial_in_command_handler {
private:
    std::thread serial_read_thread;

    static serial_in_command_handler* instance;
    serial_in_command_handler();
    void read_from_serial();
public:
    serial_in_command_handler(const serial_in_command_handler& obj) = delete;
    static serial_in_command_handler* getInstance();
    void run();
};


#endif //SMARTHOMEARDUINO_SERIAL_IN_COMMAND_HANDLER_H
