#include "./Interface/Potentiometer.h"

Potentiometer::Potentiometer(byte pin)
{
    m_pin = pin;
}

int Potentiometer::GetValue()
{
    int newValue = analogRead(m_pin);

    // Convert gotten value to humidity percentage.
    // Valid range of humidity on DHT11 is 20% to 90%
    m_valuePercentage = ConvertToRange(newValue, 20, 90);

    return m_valuePercentage;
}

int Potentiometer::ConvertToRange(int num, int min, int max)
{
    num = map(num, 0, 4095, min, max);

    num = constrain(num, min, max);

    return num;
}