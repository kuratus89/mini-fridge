#include "../include/main.h"

void home(){
    display.println("TEMPS:");
    String temp = "CHAMBER : " + String(getChamberTemp());
    display.println(temp);
    temp = "INSIDE : "+ String(getTempIn());
    display.println(temp);
    temp = "OUTSIDE :"+ String(getTempOut());
    display.println(temp);
    if(getDeltaEncoderPos(0))stage.push(Stage::TEMP_CHANGE);
}

void tempChange(){
    display.println(String(manualSystemData.cooling));
    int delta = getDeltaEncoderPos(1);
    manualSystemData.cooling +=delta;
    if(isEncoderPressed())stage.pop();
}
