//
// Created by Pánczél Bence on 2023. 04. 03..
//

#include "../lib/ServoESP32/src/Servo.h"
#include "servo_handler.h"

servo_handler::servo_handler(int pin):pin(pin) {
    servo.attach(pin);
}
void servo_handler::set(int pos){

}