//
// Created by Pánczél Bence on 2023. 04. 03..
//

#ifndef SMARTHOMEARDUINO_SERVO_HANDLER_H
#define SMARTHOMEARDUINO_SERVO_HANDLER_H




class servo_handler {
    const int pin;
    int position = 0;
    Servo servo;
public:
    servo_handler(int pin);
    void set(int pos);
};


#endif //SMARTHOMEARDUINO_SERVO_HANDLER_H
