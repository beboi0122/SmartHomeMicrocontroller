//
// Created by Pánczél Bence on 2023. 04. 03..
//


#include "my_servo.h"


my_servo::my_servo(int pin):pin(pin) {
    servo1 = new Servo();
    servo1->attach(this->pin);
    position = 0;
    servo1->write(position);
}

void my_servo::set(int pos) {
    if(pos > position){
        for(; position < pos; position++){
            servo1->write(position);
            delay(5);
        }
    }else if( pos < position){
        for(; position > pos; position--){
            servo1->write(position);
            delay(5);
        }
    }
}