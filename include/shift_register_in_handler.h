//
// Created by Pánczél Bence on 2023. 03. 29..
//

#ifndef SMARTHOMEARDUINO_SHIFT_REGISTER_IN_HANDLER_H
#define SMARTHOMEARDUINO_SHIFT_REGISTER_IN_HANDLER_H


#include <cstdint>

class shift_register_in_handler {
private:
    const int shift_register_number;
    const int latchPin;
    const int dataPin;
    const int clockPin;
    uint8_t* dat;
    uint8_t* dat_before;
    std::thread shift_in_thread;
public:
    shift_register_in_handler(int latchPin, int dataPin, int clockPin, int shift_register_number);
    void run();
};


#endif //SMARTHOMEARDUINO_SHIFT_REGISTER_IN_HANDLER_H
