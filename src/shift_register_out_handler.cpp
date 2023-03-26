//
// Created by Pánczél Bence on 2023. 03. 19..
//

#include <Arduino.h>
#include "shift_register_out_handler.h"
#include <cmath>

shift_register_out_handler::shift_register_out_handler(const int latchPin, const int dataPin,
                                                       const int clockPin, const int shift_register_number)
        :latchPin(latchPin), dataPin(dataPin), clockPin(clockPin), shift_register_number(shift_register_number){
    pinMode(this->latchPin, OUTPUT);
    pinMode(this->clockPin, OUTPUT);
    pinMode(this->dataPin, OUTPUT);
    dat = new uint8_t[shift_register_number];
    digitalWrite(latchPin, LOW);
    for(int i = shift_register_number-1; i >= 0; i--){
        dat[i] = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, dat[i]);
    }
    digitalWrite(latchPin, HIGH);
}

void shift_register_out_handler::setDat(const uint8_t* dat_in) {
    digitalWrite(latchPin, LOW);
    for(int i = shift_register_number-1; i >= 0; i--){
        this->dat[i] = dat_in[i];
        shiftOut(dataPin, clockPin, MSBFIRST, dat[i]);
    }
    digitalWrite(latchPin, HIGH);

}

void shift_register_out_handler::flipPin(unsigned int pin) {
    int n_reg = (int)(pin/8);
    unsigned int pow_y = pin-(8*n_reg);

    int tmp = (int)pow(2, pow_y);
    if((dat[n_reg] & tmp) > 0){
        dat[n_reg] -= tmp;
    }else{
        dat[n_reg] += tmp;
    }
    Serial.print(String(n_reg) + "\n");
    Serial.print(String(dat[n_reg]) + "\n");
    Serial.print("\n");
    digitalWrite(latchPin, LOW);
    for(int i = shift_register_number-1; i >= 0; i--){
        shiftOut(dataPin, clockPin, MSBFIRST, dat[i]);
    }
    digitalWrite(latchPin, HIGH);
}


