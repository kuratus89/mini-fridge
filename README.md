# mini-fridge
it is a small fridge for diet coke . It runs on esp32 (PlatormIo and arduino framework) and gives a menu ui in oled screen ,it monitor sensors ( temperature , humidity , current/voltage) .it has 2 mode automatic and manual


## Automatic Mode
(under devlopment!)
In this mode you just have to set the desire temperature and the fridge itself will controll everything and try his 95% to reach/maintain that temprature inside the fridge!
(yeah only 95%)

## Manual Mode
In this mode you have to set every thing on your own , like how much cooling it should do? ( in percent)

# Hardware

- Esp32 (NodeMCU-32S) to control and manage all components
- SSD1306 OLED display (I2C)
- INA219 to measure current and voltage in fans and pump
- DS18B20 Temprature probe - to measure temp
- DHT22 - to measure temp and humidity
- Rotary encoder - to navigate ui
- Two Peltier module Tec1-12715 or Tec1-12730 - to maintain the desire temprature inside fridge
- Pumps and Fans

(there are other components also but this list is for the components that i can control from firmware , you can find the list of all components in bom below!)

# Libraries

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

# Schematic 
<img width="906" height="613" alt="{00911E46-8959-47F2-9295-1D12837B0314}" src="https://github.com/user-attachments/assets/c84db43f-5c9c-4cd6-997a-301cb6677663" />

# CAD

## Full body
<img width="606" height="529" alt="{6C90B3C3-C4DE-4B13-B39D-83AFB3EAACE5}" src="https://github.com/user-attachments/assets/1bc80d45-3780-47bb-95f1-cc9e2e49cd10" />
<img width="648" height="489" alt="{61141543-0FD0-4A17-90AE-6EF8423B7EC3}" src="https://github.com/user-attachments/assets/fa022ab1-bc9a-425e-b351-ec73e9f0cdce" />

## Main Chamber

<img width="415" height="409" alt="{4593166A-A573-4287-BCA8-D1BA4FFC081E}" src="https://github.com/user-attachments/assets/be3d51d2-6fee-45e7-a9d1-9d0074fec33a" />

## Door

<img width="415" height="387" alt="{906CC347-AB07-424B-85BE-3F9864C790FA}" src="https://github.com/user-attachments/assets/610ef832-dde5-4e6c-85dc-b7d903f557b9" />

## Upper Chamber 

<img width="511" height="312" alt="{BBC463F1-F698-48B9-A9F4-ABC879EF27EC}" src="https://github.com/user-attachments/assets/dffba705-a606-4f67-b7c6-a4c406804d96" />

## Back Cover

<img width="422" height="394" alt="{0966B65D-5965-4FD0-AD55-19C8B5D2FB89}" src="https://github.com/user-attachments/assets/cdc5e27c-1776-479f-a196-3ee3fb4d2cc9" />

## Lower Chamber 

<img width="412" height="382" alt="{8D0E43AC-5870-4A4B-9BEF-C23560752F2E}" src="https://github.com/user-attachments/assets/e0123fe5-511e-418f-97e1-dcd457e955d6" />

# BOM
https://docs.google.com/spreadsheets/d/1UBUqanrUFpSi6QHUGbMFJ8Iq06dwHC4YZDE9zaKxZ_s/edit?usp=sharing
