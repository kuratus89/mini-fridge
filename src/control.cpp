#include "../include/main.h"

void setFanInSpeed(uint8_t s){
    int value = (s*255)/100;
    ledcWrite(FAN_IN_CH , value);
    sensorData.fanInSpeed = s;
}

void setFanOutSpeed(uint8_t s){
    int value = (s*255)/100;
    ledcWrite(FAN_OUT_CH , value);
    sensorData.fanOutSpeed =s;
}

void setPumpSpeed(uint8_t s){
    int value = (s*255)/100;
    ledcWrite(PUMP_CH , value);
    sensorData.pumpSpeed = s;
}