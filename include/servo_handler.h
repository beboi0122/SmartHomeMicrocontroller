//
// Created by Pánczél Bence on 2023. 04. 03..
//

#ifndef SMARTHOMEARDUINO_SERVO_HANDLER_H
#define SMARTHOMEARDUINO_SERVO_HANDLER_H


#include "my_servo.h"
#include <map>


class servo_handler {
    std::map<String, my_servo*> servos;
    static servo_handler* instance;
    servo_handler();
public:
    static servo_handler* getInstance();
    void add_servo(String name, my_servo* serv);
    void set(String name, int pos);
};


#endif //SMARTHOMEARDUINO_SERVO_HANDLER_H
