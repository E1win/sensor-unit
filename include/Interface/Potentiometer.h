#pragma once

#include "./config.h"
#include "Arduino.h"

class Potentiometer
{
public:
    Potentiometer(byte pin);

    int GetValue() const;
    bool IsChanged();

private:
    byte m_pin;

    const static int minChange = 20;

    int m_valuePercentage;
    bool m_hasNewValue = false;
};