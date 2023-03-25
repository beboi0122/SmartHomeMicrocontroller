//
// Created by Pánczél Bence on 2023. 03. 19..
//

#ifndef SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
#define SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H


class shift_register_out_handler {
private:
    int latchPin;
    int dataPin;
    int clockPin;
    unsigned int dat;
public:
    void setDat(unsigned int dat);
    shift_register_out_handler(int latchPin, int dataPin, int clockPin);
    void flipPin(unsigned int pin);
};


#endif //SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
