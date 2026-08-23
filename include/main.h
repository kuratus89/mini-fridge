#pragma once
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
    FANS,
    NONE;
};
