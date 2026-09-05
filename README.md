# mini-fridge
it is a small fridge for diet coke . It runs on esp32 (PlatormIo and arduino framework) and gives a menu ui in oled screen ,it monitor sensors ( temperature , humidity , current/voltage) .it has 2 mode automatic and manual


## Automatic Mode
(under devlopment!)
In this mode you just have to set the desire temperature and the fridge itself will controll everything and try his 95% to reach/maintain that temprature inside the fridge!
(yeah only 95%)

## Manual Mode
In this mode you have to set every thing on your own , like how much cooling it should do? ( in percent)

#Hardware

- Esp32 (NodeMCU-32S) to control and manage all components
- SSD1306 OLED display (I2C)
- INA219 to measure current and voltage in fans and pump
- DS18B20 Temprature probe - to measure temp
- DHT22 - to measure temp and humidity
- Rotary encoder - to navigate ui
- Two Peltier module Tec1-12715 or Tec1-12730 - to maintain the desire temprature inside fridge
- Pumps and Fans

(there are other components also but this list is for the components that i can control from firmware , you can find the list of all components in bom below!)

## Libraries

- adafruit ssd1306
- adafruit GFX library
- DallasTemprature
- OneWire
- Adafruit INA219
- DHT sensor library

# Firmware Structure

- `include/main.h` —  pinouts , constants , type definations
- `src/main.cpp` —  Boot , display , stage system
- `src/check.cpp` —  self checks
- `src/sensor.cpp` —  sensors polling , encoder handling
- `src/control.cpp` — PWM and driver helpers for actuators
- `src/system.cpp` —  control loop (auto/manual) and safety stuff

# CAD

# Schematic

# BOM