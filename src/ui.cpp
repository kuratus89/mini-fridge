#include "../include/main.h"

void home(){
    display.fillScreen(ILI9341_BLACK);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    display.println("TEMPS:");
    String temp = "CHAMBER : " + String(getChamberTemp());
    display.println(temp);
    temp = "INSIDE : " + String(getTempIn());
    display.println(temp);
    temp = "OUTSIDE :" + String(getTempOut());
    display.println(temp);
    if(getDeltaEncoderPos(0)) stage.push(Stage::TEMP_CHANGE);
}

void tempChange(){
    display.fillScreen(ILI9341_BLACK);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    display.println(String(manualSystemData.cooling));
    int delta = getDeltaEncoderPos(1);
    manualSystemData.cooling += delta;
    if(isEncoderPressed()) stage.pop();
}
