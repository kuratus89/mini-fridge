#include "../include/main.h"



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

static inline void checkTemp1(bool init){  
  int temp =0;
  bool fail=0;

  if(init){
    if(tempSensor.getDeviceCount() <2)fail=1;
  }


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
static inline void checkPump(bool init){
  bool fail=0;
  //check here->
  if(init && (!pump.begin()))fail=1;

  if(fail){
    pushLog("PUMP FAIL" ,LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  pushLog("PUMP PASS" , LogLevel::INFO);
  checkStage = Sensor::FANIN;
}

static inline void checkFanIN(bool init){
  bool fail=0;
  if(init && (!fan_in.begin()))fail=1;
  if(fail){
    pushLog("FAN FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  pushLog("FAN PASS" , LogLevel::INFO);
  checkStage = Sensor::FANOUT;
}

static inline void checkFanOUT(bool init){
  bool fail=0;
  if(init && (!fan_out.begin()))fail=1;

  if(fail){
    pushLog("FAN FAIL" , LogLevel::ERRO);
    stage = Stage::ERROR_STAGE;
    return;
  }
  pushLog("FAN PASS" , LogLevel::INFO);
  checkStage = Sensor::NONE;
}


 void checkUpStage(bool init){
  switch(checkStage){
    case Sensor::SCREEN:checkScreen();break;
    case Sensor::POWER_SUPPLY:checkPowerSupply();break;
    case Sensor::TEMP1:checkTemp1(1);break;
    case Sensor::TEMP2:checkTemp2();break;
    case Sensor::PELTIER1:checkPeltier1();break;
    case Sensor::PELTIER2:checkPeltier2();break;
    case Sensor::PUMP:checkPump(init);break;
    case Sensor::FANIN:checkFanIN(init);break;
    case Sensor::FANOUT:checkFanOUT(init);break;
    case Sensor::NONE:stage = Stage::HOME_STAGE;
  }
  displayLog();
}