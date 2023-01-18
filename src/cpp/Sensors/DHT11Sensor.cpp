#include "Sensors/DHT11Sensor.h"

DHT11Sensor::DHT11Sensor(byte pin, uint8_t type) : m_dht(pin, type)
{
}

void DHT11Sensor::Start()
{
    m_dht.begin();

    sensor_t sensor;

    m_dht.temperature().getSensor(&sensor);

    delayMS = sensor.min_delay / 1000;

    // Remember to reserve enough bytes for task.

    xTaskCreate(
        Loop,          // Task to be executed
        "DHT11Sensor", // Name of task (for debugging)
        4000,          // Bytes to reserve for task
        this,          // Parameters
        1,             // Priority
        NULL           // Handler
    );
}

void DHT11Sensor::Loop(void *params)
{
    DHT11Sensor *instance = (DHT11Sensor *)params;

    for (;;)
    {
        Serial.println("Reading values from sensor...");

        sensors_event_t event;

        // Get temperature
        instance->m_dht.temperature().getEvent(&event);
        if (isnan(event.temperature))
        {
            Serial.println("Error reading temperature!");
        }
        else
        {
            instance->m_temperature = event.temperature;
        }

        // Get humidity
        instance->m_dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity))
        {
            Serial.println("Error reading humidity!");
        }
        else
        {
            instance->m_humidity = event.relative_humidity;
        }

        // Delay to give IDLE task time to execute.
        vTaskDelay(2500);
    }
}

float DHT11Sensor::GetTemperature() const
{
    return m_temperature;
}

float DHT11Sensor::GetHumidity() const
{
    return m_humidity;
}