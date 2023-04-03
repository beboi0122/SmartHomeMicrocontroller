//
// Created by Pánczél Bence on 2023. 04. 03..
//

#include <map>
#include "my_servo.h"
#include "servo_handler.h"

servo_handler* servo_handler::instance = nullptr;

servo_handler::servo_handler() = default;

servo_handler *servo_handler::getInstance() {
    if(!instance)
        instance = new servo_handler();
    return instance;
}

void servo_handler::add_servo(String name, my_servo *serv) {
    servos.insert(std::make_pair(name, serv));
}

void servo_handler::set(String name, int pos) {
    servos[name]->set(pos);
}
