#pragma once

#include "./config.h"
#include "./Interface/Potentiometer.h"
#include "./Sensors/DHT11Sensor.h"

class App
{
public:
    App();

    void Run();

private:
    Potentiometer m_ptnmtr;
    DHT11Sensor m_dht11;

    int m_temperature;
    int m_humidity;

    int m_idealTemperature;
    int m_idealHumidity;
};