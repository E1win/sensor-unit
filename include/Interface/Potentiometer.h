#pragma once

#include "./config.h"
#include "Arduino.h"

class Potentiometer
{
public:
    Potentiometer(byte pin);

    int GetValue();

private:
    int ConvertToRange(int num, int min, int max);

private:
    byte m_pin;

    int m_value;

    int m_valuePercentage;
};