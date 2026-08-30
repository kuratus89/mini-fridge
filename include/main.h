#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <deque>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>

#define NIL -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LOGO_NAME "KURA"
#define CHECKUP_DELAY 350
#define MAX_LOGS 8
#define LOG_TEXT_SIZE 1
#define LOG_DISPLAY_LINE (SCREEN_HEIGHT/(8*LOG_TEXT_SIZE))
#define TEMP_SENSOR_DELAY 150
#define PELTIER_SENSOR_DELAY 500
#define FAN_SENSOR_DELAY 2000

// PINS
#define LED_PIN 2
#define SDA 22
#define SCL 23
#define TEMP_PIN 32
#define CHAMBER_TEMP_MOIST_PIN 25
#define ROTARY_ENCODER_SW 12
#define ROTARY_ENCODER_CLK 36
#define ROTARY_ENCODER_DT 39
#define FAN_OUT_PIN 26
#define FAN_IN_PIN 27
#define PUMP_PINP 14
#define PELTIER1_R_IS 18
#define PELTIER1_L_IS 5
#define PELTIER1_RPWM 17
#define PELTIER1_LPWM 16
#define PELTIER2_L_IS 2
#define PELTIER2_R_IS 23
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

    float peltier1Voltage=NIL;
    float peltier1Current=NIL;
    float peltier1Energy=NIL;
    unsigned long peltier1Delay=NIL;

    float peltier2Voltage=NIL;
    float peltier2Current=NIL;
    float peltier2Energy=NIL;
    unsigned long peltier2Delay=NIL;

    float pumpVoltage=NIL;
    float pumpCurrent=NIL;
    float pumpEnergy=NIL;
    unsigned long pumpDelay = NIL;

    float fanInVoltage=NIL;
    float fanInCurrent=NIL;
    float fanInEnergy=NIL;
    unsigned long fanInDelay =NIL;

    float fanOutVoltage=NIL;
    float fanOutCurrent=NIL;
    float fanOutEnergy=NIL;
    unsigned long fanOutDelay = NIL;
};
extern SensorData sensorData;

extern Stage stage;
extern Sensor checkStage;

extern Adafruit_SSD1306 display(SCREEN_WIDTH , SCREEN_HEIGHT , &Wire , -1);
extern Adafruit_INA219 pump(0x40);
extern Adafruit_INA219 fan_in(0x41);
extern Adafruit_INA219 fan_out(0x42);
extern OneWire oneWire(TEMP_PIN);
extern DallasTemperature tempSensor(&oneWire);


void pushLog(String , LogLevel);
void displayLog();


void checkUpStage(bool);