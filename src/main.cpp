#include "../include/main.h"

//Global variables 
Stage stage;
Sensor checkStage;
std::deque<String> sysLog;

Adafruit_SSD1306 display(SCREEN_WIDTH , SCREEN_HEIGHT , &Wire , -1);
Adafruit_INA219 pump(0x40);
Adafruit_INA219 fan_in(0x41);
Adafruit_INA219 fan_out(0x42);
OneWire oneWire(TEMP_PIN);
DallasTemperature tempSensor(&oneWire);
SensorData sensorData;

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
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  pinMode(LED_PIN , OUTPUT);
  digitalWrite(LED_PIN , HIGH);
  Wire.begin(SDA , SCL);
  stage = Stage::BOOT_STAGE;
  checkStage = Sensor::SCREEN;

  pump.begin();
  fan_in.begin();
  fan_out.begin();
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

void displayLog(){
  int  visibleLine = min((int)sysLog.size() , LOG_DISPLAY_LINE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(LOG_TEXT_SIZE);
  for(int i=sysLog.size() - visibleLine ; i<sysLog.size() ; i++)display.println(sysLog[i]);
  display.display();
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





static inline void errorStage(){
  displayLog();
  digitalWrite(LED_PIN , HIGH);
  delay(10);
  digitalWrite(LED_PIN , LOW);
  delay(15);
}




void loop() {
  switch(stage){
    case Stage::ERROR_STAGE:errorStage();break;
    case Stage::BOOT_STAGE:bootLogo();break;
    case Stage::CHECKUP_STAGE:checkUpStage(1);break;
    case Stage::HOME_STAGE:while(1);
  }
}

