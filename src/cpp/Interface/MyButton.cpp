#include "./Interface/MyButton.h"

MyButton::MyButton(byte pin)
{
    m_pin = pin;

    m_prevState = HIGH;
    m_state = HIGH;
}

bool MyButton::IsPressed()
{
    m_prevState = m_state;

    m_state = digitalRead(m_pin);

    if (m_prevState == HIGH && m_state == LOW)
    {
        return true;
    }

    return false;
}