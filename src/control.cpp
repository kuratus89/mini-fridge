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

static void driverBridge(uint8_t rpwmCH , uint8_t lpwmCH , uint8_t percent){
    percent =constrain(percent , (uint8_t)-100 , (uint8_t)100);
    int value = (abs(percent)*255)/100;

    if(percent>0){
        ledcWrite(rpwmCH , value);
        ledcWrite(lpwmCH , 0);
    }
    else {
        ledcWrite(rpwmCH , 0);
        ledcWrite(lpwmCH , value);
    }
}

void setPeltier1(int8_t percent){
    driverBridge(PELTIER1_RPWM_CH , PELTIER1_LPWM_CH , percent);
    sensorData.peltier1Speed = percent;
}

void setPeltier2(int8_t percent){
    driverBridge(PELTIER2_RPWM , PELTIER2_LPWM , percent);
    sensorData.peltier2Speed = percent;
}