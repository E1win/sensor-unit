#pragma once

#include "Arduino.h"

class MyButton
{
public:
    MyButton(byte pin);

    bool IsPressed();

private:
    byte m_pin;

    bool m_prevState;
    bool m_state;
};