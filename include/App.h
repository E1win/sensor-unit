#pragma once

#include "./config.h"

#include "./Interface/Display.h"
#include "./Interface/Potentiometer.h"
#include "./Interface/Alarm.h"
#include "./Interface/MyButton.h"

#include "./Sensors/DHT11Sensor.h"

#include "./Net/DataSender.h"

class App
{
public:
    App();

    void Run();

private:
    bool WithinRange(float currValue, float idealValue, float maxDifference);

private:
    Potentiometer m_ptnmtr;
    DHT11Sensor m_dht11;
    Alarm m_alarm;
    Display m_display;
    DataSender m_dataSender;
    MyButton m_btn1;
    MyButton m_btn2;

    float m_temperature;
    float m_humidity;

    float m_idealTemperature = 24.f;
    float m_idealHumidity = 50.f;

    float m_maxTemperatureDeviation = 2.f;
    float m_maxHumidityDeviation = 10.f;
};