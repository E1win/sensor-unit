#pragma once

#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "DHT_U.h"

class DHT11Sensor
{
public:
    DHT11Sensor(byte pin, uint8_t type);

    void Start();

    float GetTemperature() const;
    float GetHumidity() const;

private:
    static void Loop(void *params);

private:
    byte m_pin;
    uint8_t m_type;

    DHT_Unified m_dht;

    float m_temperature;
    float m_humidity;

    int delayMS;
};