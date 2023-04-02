//
// Created by Pánczél Bence on 2023. 03. 19..
//

#ifndef SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
#define SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H


class shift_register_out_handler {
private:
    int shift_register_number;
    int latchPin;
    int dataPin;
    int clockPin;
    uint8_t* dat;
    static shift_register_out_handler* instance;
    shift_register_out_handler();
public:
    static shift_register_out_handler* getInstance();
    void setUp(int latchPin, int dataPin, int clockPin, int shift_register_number);
    void setDat(const uint8_t* dat);
    void flipPin(unsigned int pin);
    void setPin(unsigned int pin, unsigned int val);
};


#endif //SMARTHOME_SHIFT_REGISTER_OUT_HANDLER_H
