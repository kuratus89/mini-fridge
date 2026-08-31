#include "../include/main.h"
void updateTemps(){
    unsigned long current = millis();
    if(current - sensorData.tempDelay <TEMP_SENSOR_DELAY)return;
    sensorData.tempDelay = current;
    tempSensor.requestTemperatures();
    sensorData.tempin = tempSensor.getTempCByIndex(0);// reminder :once i get temp probe irl i will use address instead of index
    sensorData.tempout = tempSensor.getTempCByIndex(1);
    // if(sensorData.tempin == DEVICE_DISCONNECTED_C)return ;
    // if(sensorData.tempout == DEVICE_DISCONNECTED_C)return ;
}

void updateFanIn(){
    unsigned long current = millis();
    if(current - sensorData.fanInDelay < FAN_SENSOR_DELAY)return;
    sensorData.fanInDelay = current;
    sensorData.fanInVoltage = fan_in.getBusVoltage_V();
    sensorData.fanInCurrent = fan_in.getCurrent_mA();
    sensorData.fanInEnergy = fan_in.getPower_mW();
}

void updateFanOut(){
    unsigned long current = millis();
    if(current - sensorData.fanOutDelay < FAN_SENSOR_DELAY)return;
    sensorData.fanOutDelay = current;
    sensorData.fanOutVoltage = fan_out.getBusVoltage_V();
    sensorData.fanOutCurrent = fan_out.getCurrent_mA();
    sensorData.fanOutEnergy = fan_out.getPower_mW();
}

void updatePump(){
    unsigned long current = millis();
    if(current - sensorData.pumpDelay <PUMP_SENSOR_DELAY)return;
    sensorData.pumpDelay = current;
    sensorData.pumpVoltage = pump.getBusVoltage_V();
    sensorData.pumpCurrent = pump.getCurrent_mA();
    sensorData.pumpEnergy = pump.getPower_mW();
}

bool updatePeltier1(){
    unsigned long current = millis();
    if(current - sensorData.peltier1Delay <PELTIER_SENSOR_DELAY)return;
    sensorData.peltier1Delay = current;

}


