#pragma once

#include <TFT_eSPI.h>
#include "config.h"

class Display
{
public:
    Display();

    void Init();
    void Reset();

    void Update(float temperature, float idealTemperature, float humidity, float idealHumidity);

private:
private:
    TFT_eSPI m_tft;
    TFT_eSprite m_sprite;
};