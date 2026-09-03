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

static inline float readCurrent(int pin){
    int raw = analogRead(pin);
    float v = (raw/ADC_MAX)* ADC_VREF;
    float i_sense = v/R_SENSE;
    float i_motor = i_sense*K_ILIS;
    return i_motor;
}

void updatePeltier1(){
    unsigned long current_time = millis();
    if(current_time - sensorData.peltier1Delay <PELTIER_SENSOR_DELAY)return;
    sensorData.peltier1Delay = current_time;
    float current = max(readCurrent(PELTIER1_R_IS) , readCurrent(PELTIER1_L_IS));
    sensorData.peltier1Current = current;
    sensorData.peltier1Energy = current*12;   
}

void updatePeltier2(){
    unsigned long current_time = millis();
    if(current_time - sensorData.peltier2Delay < PELTIER_SENSOR_DELAY)return;
    sensorData.peltier2Delay = current_time;
    float current = max(readCurrent(PELTIER2_R_IS) , readCurrent(PELTIER2_L_IS));
    sensorData.peltier2Current = current;
    sensorData.peltier2Energy = current*12;
}




void updateAllSensors(){
    updateTemps();
    updateFanIn();
    updateFanOut();
    updatePump();
    updatePeltier1();
    updatePeltier2();
}

volatile int32_t encoderPos =0;

volatile bool encoderBtnPressed = 0;

static volatile uint8_t lastState =0;
static unsigned long lastBtnMillis =0;

void IRAM_ATTR encoderISR(){
    uint8_t clk = digitalRead(ROTARY_ENCODER_CLK);
    uint8_t dt = digitalRead(ROTARY_ENCODER_DT);
    uint8_t state = (clk<<1)| dt;

    if(clk==LOW){
        if(dt ==HIGH)encoderPos++;
        else encoderPos--;
    }
    lastState = state;
}

void IRAM_ATTR encoderBtnISR(){
    unsigned long now = millis();
    if(now - lastBtnMillis > DEBOUNCE_MS){
        encoderBtnPressed = 1;
        lastBtnMillis = now;
    }
}

void setupEncoder(){
    attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_CLK) , encoderISR , FALLING);
    attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_SW) , encoderBtnISR , FALLING);
}

static uint8_t lastEncoderPos=0;

int getDeltaEncoderPos(){
    int delta = encoderPos - lastEncoderPos;
    lastEncoderPos = encoderPos;
    return delta;
}

bool isEncoderPressed(){
    bool value = encoderBtnPressed;
    encoderBtnPressed =0;
    return value;
}