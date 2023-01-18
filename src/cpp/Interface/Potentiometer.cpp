#include "./Interface/Potentiometer.h"

Potentiometer::Potentiometer(byte pin)
{
    m_pin = pin;

    int value = analogRead(m_pin);

    m_value = value;

    // Fill pastReadings with current reading
    for (int i = 0; i < trackedReadings; i++)
    {
        m_pastReadings[i] = value;
    }

    Serial.print("Initial reading: ");
    Serial.println(value);

    m_prevPercentage = ConvertToRange(m_median, 20, 90);
    m_prevPrevPercentage = m_prevPercentage;
}

int Potentiometer::GetValue()
{
    int newValue = analogRead(m_pin);

    InsertReading(newValue);

    if (abs(m_pastReadings[1] - newValue) < 5)
    {
        int temp = m_prevPercentage;
        m_prevPercentage = m_valuePercentage;
        m_prevPrevPercentage = temp;
        return m_valuePercentage;
    }

    Serial.print("Reading: ");
    Serial.println(newValue);

    // Insert new reading in past reading array.
    InsertReading(newValue);

    Serial.print("Median: ");
    Serial.println(m_median);

    // apply exponential smoothing on median value
    m_value += (newValue - m_value) / 4;

    Serial.print("Smoothed Median: ");
    Serial.println(m_value);

    // Convert gotten value to humidity percentage.
    // Valid range of humidity on DHT11 is 20% to 90%

    m_valuePercentage = ConvertToRange(m_median, 20, 90);

    Serial.print("Curr Percentage: ");
    Serial.println(m_valuePercentage);

    if (abs(m_valuePercentage - m_prevPercentage) == 1 && abs(m_valuePercentage - m_prevPrevPercentage) == 1)
    {
        // return previous percentage

        int temp = m_prevPercentage;
        m_prevPercentage = m_valuePercentage;
        m_prevPrevPercentage = temp;
        Serial.println("Returned prev percentage");

        return temp;
    }

    Serial.println("Returned current percentage");
    Serial.println("--------");

    int temp = m_prevPercentage;
    m_prevPercentage = m_valuePercentage;
    m_prevPrevPercentage = temp;

    return m_valuePercentage;
}

void Potentiometer::InsertReading(int value)
{
    int temp;

    int min = value;
    int max = value;
    m_median = value;

    // 3, 5, 5

    for (int i = 0; i < trackedReadings; i++)
    {
        temp = m_pastReadings[i];
        m_pastReadings[i] = value;

        if (value <= min)
        {
            m_median = min;
            min = value;
        }
        else if (value >= max)
        {
            m_median = max;
            max = value;
        }
        else
        {
            m_median = value;
        }

        value = temp;
    }

    // Serial.print("Min: ");
    // Serial.print(min);
    // Serial.print("Max: ");
    // Serial.print(max);
}

int Potentiometer::GetAverageOfReadings()
{
    int total = m_pastReadings[0];

    for (int i = 1; i < trackedReadings; i++)
    {
        total += m_pastReadings[i];
    }

    return total / trackedReadings;
}

int Potentiometer::ConvertToRange(int num, int min, int max)
{
    num = map(num, 0, 4095, min, max);

    num = constrain(num, min, max);

    return num;
}