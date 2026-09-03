#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stack>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>

#define NIL -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LOGO_NAME "KURA"
#define MAX_LOGS 8
#define LOG_TEXT_SIZE 1
#define LOG_DISPLAY_LINE (SCREEN_HEIGHT/(8*LOG_TEXT_SIZE))
#define TEMP_SENSOR_DELAY 150
#define PELTIER_SENSOR_DELAY 250
#define FAN_SENSOR_DELAY 2000
#define PUMP_SENSOR_DELAY 1500
#define R_SENSE 1000.0
#define K_ILIS 8500.0
#define ADC_VREF 3.3
#define ADC_MAX 4095.0
#define DEBOUNCE_MS 200
#define PUMP_CH 0
#define FAN_IN_CH 1
#define FAN_OUT_CH 2
#define PWM_FREQ 20000
#define PWM_RES 8 
#define PELTIER1_RPWM_CH 3
#define PELTIER1_LPWM_CH 4
#define PELTIER2_RPWM_CH 5
#define PELTIER2_LPWM_CH 6
// PINS
#define LED_PIN 2
#define SDA 21
#define SCL 22
#define TEMP_PIN 23
#define CHAMBER_TEMP_MOIST_PIN 25
#define ROTARY_ENCODER_SW 12
#define ROTARY_ENCODER_CLK 36
#define ROTARY_ENCODER_DT 39
#define FAN_OUT_PIN 26
#define FAN_IN_PIN 27
#define PUMP_PIN 14
#define PELTIER1_R_IS 34
#define PELTIER1_L_IS 35
#define PELTIER1_RPWM 17
#define PELTIER1_LPWM 16
#define PELTIER2_L_IS 33
#define PELTIER2_R_IS 32
#define PELTIER2_RPWM 4
#define PELTIER2_LPWM 19






#define LOGO_WIDTH 32
#define LOGO_HEIGHT 32


enum class Stage{
    BOOT_STAGE,
    CHECKUP_STAGE,
    ERROR_STAGE,
    HOME_STAGE,
};

enum class LogLevel{
    INFO ,
    WARN ,
    ERRO , 
};

enum class Sensor{
    SCREEN,
    POWER_SUPPLY,
    TEMP1,
    TEMP2,
    PELTIER1,
    PELTIER2,
    PUMP,
    FANIN,
    FANOUT,
    NONE,
};

class SensorData{
    public:
    float tempin=NIL;
    float tempout=NIL;
    unsigned long tempDelay=NIL;

    float peltier1Current=NIL;
    float peltier1Energy=NIL;
    int peltier1Speed =0;
    unsigned long peltier1Delay=NIL;

    float peltier2Current=NIL;
    float peltier2Energy=NIL;
    int peltier2Speed = 0;
    unsigned long peltier2Delay=NIL;

    float pumpVoltage=NIL;
    float pumpCurrent=NIL;
    float pumpEnergy=NIL;
    uint8_t pumpSpeed = 0;
    unsigned long pumpDelay = NIL;

    float fanInVoltage=NIL;
    float fanInCurrent=NIL;
    float fanInEnergy=NIL;
    uint8_t fanInSpeed = 0;
    unsigned long fanInDelay =NIL;

    float fanOutVoltage=NIL;
    float fanOutCurrent=NIL;
    float fanOutEnergy=NIL;
    uint8_t fanOutSpeed =0;
    unsigned long fanOutDelay = NIL;
};
extern SensorData sensorData;

extern std::stack<Stage> stage;
extern Sensor checkStage;

extern Adafruit_SSD1306 display;
extern Adafruit_INA219 pump;
extern Adafruit_INA219 fan_in;
extern Adafruit_INA219 fan_out;
extern OneWire oneWire;
extern DallasTemperature tempSensor;


void pushLog(String , LogLevel);
void displayLog();



void checkUpStage(bool);

void setupEncoder();