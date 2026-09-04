#include "../include/main.h"



void autoSystem(){
    // unsigned long current = millis();
    // if(current - autoSystemData.delay < AUTO_SYSTEM_DELAY)return;
    // float& desireTemp = autoSystemData.desireTemps;
    // float& currentTemp = getTempIn();

    // float delta = currentTemp - desireTemp;

    // if(delta<=TEMP_HYSTERESIS)return;
}
void manualSystem(){
    manualSystemData.power = constrain(manualSystemData.power , (uint8_t) 0 , (uint8_t)100);
    manualSystemData.fanInSpeed = constrain(manualSystemData.fanInSpeed , (uint8_t)0 , (uint8_t)100);
    manualSystemData.fanOutSpeed = constrain(manualSystemData.fanOutSpeed , (uint8_t)0 , (uint8_t)100);

    if(manualSystemData.cooling){
        if(getPeltier1()!=manualSystemData.power)setPeltier1(manualSystemData.power);
        if(getPeltier2()!=manualSystemData.power)setPeltier2(manualSystemData.power);
    }
    else {
        if(getPeltier1()!= -manualSystemData.power)setPeltier1(-manualSystemData.power);
        if(getPeltier2()!= -manualSystemData.power)setPeltier2(-manualSystemData.power);
    }

    if(getFanInSpeed()!=manualSystemData.fanInSpeed)setFanInSpeed(manualSystemData.fanInSpeed);
    if(getFanOutSpeed()!=manualSystemData.fanOutSpeed)setFanOutSpeed(manualSystemData.fanOutSpeed);
    if(getPumpSpeed()!=manualSystemData.pumpSpeed)setPumpSpeed(manualSystemData.pumpSpeed);
}

void safetyCheck(){
    
}

void system(State &state){
    safetyCheck();
    switch(state){
        case State::OFF:return;
        case State::AUTO:autoSystem();break;
        case State::MANUAL:manualSystem();break;
    }
    updateAllSensors();
}