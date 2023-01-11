#pragma once

#include "./config.h"
#include "./Interface/Potentiometer.h"
#include "./Sensors/DHT11Sensor.h"
#include "./Interface/Alarm.h"

class App
{
public:
    App();

    void Run();

private:
    bool WithinRange(float value1, float value2, float maxDifference);

private:
    Potentiometer m_ptnmtr;
    DHT11Sensor m_dht11;
    Alarm m_alarm;

    float m_temperature;
    float m_humidity;

    float m_idealTemperature = 24.f;
    float m_idealHumidity = 50.f;
};