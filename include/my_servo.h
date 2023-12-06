//
// Created by Pánczél Bence on 2023. 04. 03..
//

#ifndef SMARTHOMEARDUINO_MY_SERVO_H
#define SMARTHOMEARDUINO_MY_SERVO_H

#include "../lib/Servo/Servo.h"

class my_servo {
    const int pin;
    int position = 0;
    Servo* servo1;
public:
    my_servo(int pin);
    void set(int pos);
};


#endif //SMARTHOMEARDUINO_MY_SERVO_H
