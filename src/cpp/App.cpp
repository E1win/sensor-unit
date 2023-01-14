#include "./App.h"

App::App() : m_ptnmtr(POTENTIOMETER_PIN),
             m_dht11(DHT_PIN, DHT_TYPE),
             m_alarm(ALARM_PIN),
             m_btn1(BUTTON1_PIN),
             m_btn2(BUTTON2_PIN)
{
}

void App::Run()
{
    Serial.begin(9600);

    while (!Serial)
    {
    };

    Serial.println("Starting program...");

    m_dataSender.Init();

    m_display.Init();

    m_dht11.Start();

    while (true)
    {
        // Store previous values
        float prevTemperature = m_temperature;
        float prevHumidity = m_humidity;
        float prevIdealTemperature = m_idealTemperature;
        float prevIdealHumidity = m_idealHumidity;

        m_temperature = m_dht11.GetTemperature();
        m_humidity = m_dht11.GetHumidity();

        m_idealHumidity = m_ptnmtr.GetValue();

        // TODO: MAKE THIS MORE BUG PROOF
        if (m_btn1.IsPressed())
        {
            Serial.println("Button 1 Pressed");
            m_idealTemperature++;
        }
        else if (m_btn2.IsPressed())
        {
            Serial.println("Button 2 Pressed");
            m_idealTemperature--;
        }

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
            m_dataSender.SendStatus(UNIT_ID, m_alarm.IsOn());

            // PRINTING FOR DEBUG
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

        // Check if current values are
        // different from previous values
        // update Display if they are
        if (
            prevTemperature != m_temperature ||
            prevIdealTemperature != m_idealTemperature ||
            prevHumidity != m_humidity ||
            prevIdealHumidity != m_idealHumidity)
        {
            m_display.Update(m_temperature, m_idealTemperature, m_humidity, m_idealHumidity);
        }

        delay(200);
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