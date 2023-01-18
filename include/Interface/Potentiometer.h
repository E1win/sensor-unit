#pragma once

#include "./config.h"
#include "Arduino.h"

class Potentiometer
{
public:
    Potentiometer(byte pin);

    int GetValue();

private:
    void InsertReading(int value);
    int GetAverageOfReadings();

    int ConvertToRange(int num, int min, int max);

private:
    byte m_pin;

    int m_value;

    static const int trackedReadings = 3;

    int m_pastReadings[trackedReadings];

    int m_prevPercentage;
    int m_prevPrevPercentage;

    int m_median;

    int m_valuePercentage;
};