//
// Created by Pánczél Bence on 2023. 03. 25..
//

#ifndef SMARTHOME_SENSOR_HANDLER_H
#define SMARTHOME_SENSOR_HANDLER_H




class sensor_handler {
    std::map<String, sensor*> sensors;
    std::vector<String> sensor_names;
    std::thread sensor_read_thread;
    void read_sensors();
    static  sensor_handler* instance;
    sensor_handler();
public:
    sensor_handler(const sensor_handler& obj) = delete;
    static sensor_handler* getInstance();
    void add_sensor(const String& sensor_name, sensor* sensor);
    void run();
};


#endif //SMARTHOME_SENSOR_HANDLER_H
