//
// Created by Pánczél Bence on 2023. 03. 29..
//

#include <thread>
#include "Arduino.h"
#include "serial_communication_handler.h"
#include "shift_register_in_handler.h"

shift_register_in_handler::shift_register_in_handler(const int latchPin, const int dataPin,
                                                       const int clockPin, const int shift_register_number)
        : latchPin(latchPin), dataPin(dataPin), clockPin(clockPin), shift_register_number(shift_register_number){
    pinMode(this->latchPin, OUTPUT);
    pinMode(this->clockPin, OUTPUT);
    pinMode(this->dataPin, INPUT);
    dat = new uint8_t[shift_register_number];
    dat_before = new uint8_t[shift_register_number];

    shift_in_thread = std::thread(&shift_register_in_handler::run, this);
    shift_in_thread.detach();

}

void shift_register_in_handler::run() {
    uint8_t value;
    while (1) {
        digitalWrite(latchPin, 0);
        digitalWrite(clockPin, 0);
        digitalWrite(clockPin, 1);
        digitalWrite(latchPin, 1);
        for (int i = 0; i < shift_register_number; ++i) {
            dat[i] = 0;
            for (int j = 0; j < 8; j++) {
                value = digitalRead(dataPin);

                if (value) {
                    int a = (1 << j);
                    dat[i] =  dat[i] | a;
                }
                digitalWrite(clockPin, LOW);
                digitalWrite(clockPin, HIGH);
            }
        }
        for (int i = 0; i < shift_register_number; ++i) {
            if (dat_before[i] != dat[i]){
                String out = R"({"shift_register_in": {"values": [)" ;
                for (int j = 0; j < shift_register_number; j++){
                    if(j < shift_register_number-1)
                        out +=  " " + String(dat[j]) + ",";
                    else
                        out += " " + String(dat[j]) + " ";
                    dat_before[j] = dat[j];
                }
                out += "] }}\n";
                serial_communication_handler::getInstance()->send_interrupt(out);
                break;
            }
        }
        delay(20);
    }
}
