//
// Created by Pánczél Bence on 2023. 03. 19..
//

#ifndef SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
#define SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H


class shift_register_out_handler {
private:
    const int shift_register_number;
    const int latchPin;
    const int dataPin;
    const int clockPin;
    uint8_t* dat;
public:
    void setDat(const uint8_t* dat);
    shift_register_out_handler(int latchPin, int dataPin, int clockPin, int shift_register_number);
    void flipPin(unsigned int pin);
};


#endif //SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
