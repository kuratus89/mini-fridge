#include "../include/main.h"
#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <string>
// #include <vector>
#include <deque>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LOGO_NAME "KURA"
#define CHECKUP_DELAY 350
#define MAX_LOGS 8
#define LOG_TEXT_SIZE 1
#define LOG_DISPLAY_LINE (SCREEN_HEIGHT/(8*LOG_TEXT_SIZE))

// PINS
#define LED_PIN 2
#define OLED_SDA 22
#define OLED_SCL 23

Adafruit_SSD1306 display(SCREEN_WIDTH , SCREEN_HEIGHT , &Wire , -1);

#define LOGO_WIDTH 32
#define LOGO_HEIGHT 32

//Global variables 
Stage stage;
Sensor checkStage;
std::deque<String> sysLog;

const unsigned char logo[] PROGMEM = {
0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00,
0x00, 0x03, 0xC0, 0x00,
0x00, 0x0C, 0x20, 0x00,
0x00, 0x10, 0x1C, 0x00,
0x00, 0x60, 0x06, 0x00,
0x01, 0xC0, 0x03, 0x80,
0x03, 0x00, 0x01, 0xC0,
0x0F, 0x00, 0x00, 0x70,
0x1F, 0xC0, 0x01, 0xF8,
0x11, 0xF0, 0x07, 0x98,
0x10, 0x7C, 0x1F, 0x18,
0x1C, 0x1E, 0x78, 0x08,
0x1F, 0xC7, 0xC0, 0x08,
0x13, 0xE1, 0x80, 0x18,
0x10, 0x39, 0x80, 0x38,
0x10, 0x1D, 0x80, 0xC8,
0x18, 0x0F, 0x81, 0x88,
0x18, 0x07, 0x8F, 0x88,
0x1C, 0x03, 0xFC, 0x88,
0x17, 0x81, 0xE0, 0xC8,
0x11, 0xC1, 0x80, 0xC8,
0x09, 0xFF, 0x80, 0xD8,
0x05, 0x9F, 0x80, 0x60,
0x03, 0x87, 0x80, 0xC0,
0x01, 0xC1, 0x83, 0x80,
0x00, 0x61, 0x8E, 0x00,
0x00, 0x19, 0xB8, 0x00,
0x00, 0x07, 0xC0, 0x00,
0x00, 0x02, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00,
};


void boot(){
  Serial.begin(115200);
  pinMode(LED_PIN , OUTPUT);
  digitalWrite(LED_PIN , HIGH);
  Wire.begin(OLED_SDA , OLED_SCL);
  stage = Stage::BOOT_STAGE;
  checkStage = Sensor::SCREEN;
}


void displayBootLogo(){
  display.clearDisplay();
  display.drawBitmap((SCREEN_WIDTH - LOGO_WIDTH)/2 , (SCREEN_HEIGHT - LOGO_HEIGHT)/2 , logo , 32 , 32 ,SSD1306_WHITE);
  
  display.setCursor((SCREEN_WIDTH - (4*6))/2 , ((SCREEN_HEIGHT - LOGO_HEIGHT)/2)+LOGO_HEIGHT + 1 );
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.println(LOGO_NAME);
  display.display();
}

void pushLog(String value , LogLevel logLevel){
    String log;
    switch(logLevel){
      case LogLevel::INFO:log = "I";break;
      case LogLevel::WARN:log = "W";break;
      case LogLevel::ERRO:log = "E";break;
    }
    log = "[" + log + "]" + " " + value;
    Serial.println(log);
    sysLog.push_back(log);
    while(sysLog.size()>MAX_LOGS)sysLog.pop_front();
}

void setup() {
  boot();
  if(!display.begin(SSD1306_SWITCHCAPVCC , 0x3C)){
    pushLog("Oled not found" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }

  displayBootLogo();
  delay(1000);
}



static inline void bootLogo(){
  displayBootLogo();
  delay(1000);
  stage = Stage::CHECKUP_STAGE;
}

static inline void checkScreen(){
  // already checked after boot
  String val ="SCR ("+String(SCREEN_WIDTH) + ","+ String(SCREEN_HEIGHT) + ")";
  pushLog(val , LogLevel::INFO);
  checkStage = Sensor::POWER_SUPPLY;
}

static inline void checkPowerSupply(){
  // i think if this code is running , then power Supply is working?
  // why did i even add this function?

  checkStage = Sensor::TEMP1;
}

static inline void checkTemp1(){
  
  // check temps? idk how to do that!

  int temp =0;
  bool fail=0;

  // check code here->



  if(fail){
    pushLog("TEMP1 FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  String log = "TEMP1:" + String(temp) + "C";
  pushLog(log , LogLevel::INFO);
  checkStage = Sensor::TEMP2;
}
static inline void checkTemp2(){
  // temp 2 ? , we have 2 temp sensor?

  int temp =0;

  bool fail =0;

  if(fail){
    pushLog("TEMP2 FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  String log = "TEMP2:" + String(temp) + "C";
  pushLog(log , LogLevel::INFO);
  checkStage = Sensor::PELTIER1;
}

static inline void checkPeltier1(){

  int v =0;
  int i =0;
  int w =0;
  bool fail= 0;
  //check code here->

  if(fail){
    pushLog("PELT1 FAIL" ,LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  String log = "PELT1 PASS";
  pushLog(log , LogLevel::INFO);
  checkStage = Sensor::PELTIER2;
}

static inline void checkPeltier2(){
  int v=0;
  int i=0;
  int w=0;
  bool fail=0;

  if(fail){
    pushLog("PELT2 FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }

  String log = "PELT2 PASS";
  pushLog(log , LogLevel::INFO);
  checkStage = Sensor::PUMP;
}
static inline void checkPump(){
  bool fail=0;
  //check here->

  if(fail){
    pushLog("PUMP FAIL" ,LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  pushLog("PUMP PASS" , LogLevel::INFO);
  checkStage = Sensor::FANS;
}

static inline void checkFans(){
  bool fail=0;

  if(fail){
    pushLog("FAN FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  pushLog("FAN PASS" , LogLevel::INFO);
  checkStage = Sensor::NONE;
}

void displayLog(){
  int  visibleLine = min((int)sysLog.size() , LOG_DISPLAY_LINE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(LOG_TEXT_SIZE);
  for(int i=sysLog.size() - visibleLine ; i<sysLog.size() ; i++)display.println(sysLog[i]);
  display.display();
}


static inline void errorStage(){
  displayLog();
  digitalWrite(LED_PIN , HIGH);
  delay(10);
  digitalWrite(LED_PIN , LOW);
  delay(15);
}

static inline void checkUpStage(){
  switch(checkStage){
    case Sensor::SCREEN:checkScreen();break;
    case Sensor::POWER_SUPPLY:checkPowerSupply();break;
    case Sensor::TEMP1:checkTemp1();break;
    case Sensor::TEMP2:checkTemp2();break;
    case Sensor::PELTIER1:checkPeltier1();break;
    case Sensor::PELTIER2:checkPeltier2();break;
    case Sensor::PUMP:checkPump();break;
    case Sensor::FANS:checkFans();break;
    case Sensor::NONE:stage = Stage::HOME_STAGE;
  }
  displayLog();

}


void loop() {
  switch(stage){
    case Stage::ERROR_STAGE:errorStage();break;
    case Stage::BOOT_STAGE:bootLogo();break;
    case Stage::CHECKUP_STAGE:checkUpStage();break;
    case Stage::HOME_STAGE:while(1);
  }
}

