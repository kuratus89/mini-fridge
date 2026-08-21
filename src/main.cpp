#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// PINS
#define LED_PIN 2
#define OLED_SDA 22
#define OLED_SCL 23

Adafruit_SSD1306 display(SCREEN_WIDTH , SCREEN_HEIGHT , &Wire , -1);

int cnt =0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN , OUTPUT);
  digitalWrite(LED_PIN , HIGH);
  Wire.begin(OLED_SDA , OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC , 0x3C)){
    Serial.println("oled not found!");
    return;
  }
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);

}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(cnt);
  cnt++;
  display.display();
  String ser = "display number " + String(cnt);
  Serial.println(ser);
  // delay(5);
}

