#pragma once

#include "./config.h"

#include "./Interface/Display.h"
#include "./Interface/Potentiometer.h"
#include "./Interface/Alarm.h"

#include "./Sensors/DHT11Sensor.h"

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
    Display m_display;

    float m_temperature;
    float m_humidity;

    float m_idealTemperature = 24.f;
    float m_idealHumidity = 50.f;
};