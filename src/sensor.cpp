#include "../include/main.h"
bool updateTemps(){
    unsigned long current = millis();
    if(current - sensorData.tempDelay <TEMP_SENSOR_DELAY)return;
    sensorData.tempDelay = current;
    tempSensor.requestTemperatures();
    sensorData.tempin = tempSensor.getTempCByIndex(0);// reminder :once i get temp probe irl i will use address instead of index
    sensorData.tempout = tempSensor.getTempCByIndex(1);
    if(sensorData.tempin == DEVICE_DISCONNECTED_C)return 0;
    if(sensorData.tempout == DEVICE_DISCONNECTED_C)return 0;
    return 1;
}

bool updatefanIn(){
    unsigned long current = millis();
    if(current - sensorData.fanInDelay < FAN_SENSOR_DELAY)return;
    sensorData.fanInDelay = current;

}

bool updatePeltier1(){
    unsigned long current = millis();
    if(current - sensorData.peltier1Delay <PELTIER_SENSOR_DELAY)return;
    sensorData.peltier1Delay = current;

}