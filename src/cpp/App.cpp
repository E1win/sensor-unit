#include "./App.h"

App::App() : m_ptnmtr(POTENTIOMETER_PIN),
             m_dht11(DHT_PIN, DHT_TYPE),
             m_alarm(ALARM_PIN)
{
}

void App::Run()
{
    Serial.begin(9600);

    while (!Serial)
    {
    };

    Serial.println("Starting program...");

    m_dht11.Start();

    while (true)
    {
        m_temperature = m_dht11.GetTemperature();
        m_humidity = m_dht11.GetHumidity();

        // Get ideal humidity from potentiometer
        m_idealHumidity = m_ptnmtr.GetValue();

        // TODO: use buttons to change ideal temperature

        // PRINTING FOR DEBUG
        Serial.println(m_temperature);
        Serial.println(m_humidity);
        Serial.println(m_idealHumidity);

        // Save previous state of alarm
        bool previousState = m_alarm.IsOn();

        // Check if humidity deviates more than 10% from ideal humidity
        // or is temperature deviates more than 10% from ideal temperature

        // Need something different for temperature,
        // WithinRange will not work
        // since it is not in percentage
        if (!WithinRange(m_humidity, m_idealHumidity, 10))
        {
            m_alarm.TurnOn();
        }
        else
        {
            m_alarm.TurnOff();
        }

        // Check if state of alarm has changed.
        if (previousState != m_alarm.IsOn())
        {
            // Send new state to hub

            Serial.println("State of alarm has changed.");
            if (m_alarm.IsOn())
            {
                Serial.println("It is now on!");
            }
            else
            {
                Serial.println("It is now off!");
            }
        }

        // Optimisation: create new protothread when alarm is supposed to turn on
        // and just delete it when alarm is supposed to turn off

        delay(1000);
    }
}

bool App::WithinRange(float humidity, float idealHumidity, float maxDifference)
{
    float difference = abs(humidity - idealHumidity);

    if (difference >= maxDifference)
    {
        return false;
    }
    return true;
}