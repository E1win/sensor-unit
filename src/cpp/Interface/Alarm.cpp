#include "./Interface/Alarm.h"

Alarm::Alarm(byte pin)
{
    m_pin = pin;

    m_alarmOn = false;

    pinMode(m_pin, OUTPUT);

    xTaskCreate(
        Loop,    // Task to be executed
        "Alarm", // Name of task (for debugging)
        4000,    // Bytes to reserve for task
        this,    // Parameters
        1,       // Priority
        NULL     // Handler
    );
}

void Alarm::TurnOn()
{
    m_alarmOn = true;
}

void Alarm::TurnOff()
{
    m_alarmOn = false;
}

bool Alarm::IsOn() const
{
    return m_alarmOn;
}

void Alarm::Loop(void *params)
{
    Alarm *instance = (Alarm *)params;

    for (;;)
    {
        if (!instance->m_alarmOn)
        {
            vTaskDelay(instance->m_msDelay);
            continue;
        }

        // Turn alarm and buzzer on
        digitalWrite(instance->m_pin, HIGH);
        vTaskDelay(instance->m_msDelay);

        // Turn alarm and buzzer off
        digitalWrite(instance->m_pin, LOW);
        vTaskDelay(instance->m_msDelay);
    }
}