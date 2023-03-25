//
// Created by Pánczél Bence on 2023. 03. 19..
//

#include <Arduino.h>
#include "shift_register_out_handler.h"
#include <cmath>

shift_register_out_handler::shift_register_out_handler(int latchPin, int dataPin, int clockPin)
                                    :latchPin(latchPin), dataPin(dataPin), clockPin(clockPin), dat(0){
    pinMode(this->latchPin, OUTPUT);
    pinMode(this->clockPin, OUTPUT);
    pinMode(this->dataPin, OUTPUT);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dat);
    digitalWrite(latchPin, HIGH);
}

void shift_register_out_handler::setDat(unsigned int dat) {
    this->dat = dat;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dat);
    digitalWrite(latchPin, HIGH);
}

void shift_register_out_handler::flipPin(unsigned int pin) {
    int tmp = (int)pow(2, pin);
    if((this->dat & tmp) > 0){
        this->dat -= tmp;
    }else{
        this->dat += tmp;
    }
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, dat);
    digitalWrite(latchPin, HIGH);
}


