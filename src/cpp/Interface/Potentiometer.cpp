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

    m_valuePercentage = ConvertToRange(m_median, 20, 90);
    m_prevPercentage = m_valuePercentage;
    m_prevPrevPercentage = m_prevPercentage;
}

int Potentiometer::GetValue()
{
    int newValue = analogRead(m_pin);

    // Inserts reading in pastReadings array
    // And finds median of last few readings to
    // ignore sudden drops of voltage
    // caused by calls to sensor.
    InsertReading(newValue);

    if (abs(m_pastReadings[1] - newValue) < 25)
    {
        return m_valuePercentage;
    }

    Serial.print("Reading: ");
    Serial.println(newValue);

    Serial.print("Median: ");
    Serial.println(m_median);

    // Convert gotten value to humidity percentage.
    // Valid range of humidity on DHT11 is 20% to 90%

    int newPercentage = ConvertToRange(m_median, 20, 90);

    Serial.print("Percentage: ");
    Serial.println(newPercentage);

    Serial.println("--------");

    // Following statements are to avoid percentage fluctuating between two values
    if (newPercentage != m_valuePercentage && abs(newPercentage - m_prevPercentage) > 2)
    {
        m_prevPercentage = m_valuePercentage;
        m_valuePercentage = newPercentage;
    }

    return m_valuePercentage;
}

// Insert reading into past readings array
// Also finds median of last readings
void Potentiometer::InsertReading(int value)
{
    int temp;

    int min = value;
    int max = value;
    m_median = value;

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