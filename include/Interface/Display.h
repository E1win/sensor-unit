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

    float xPadding = 10;
    float yPadding = 10;
    float spaceForIcon = 40;

    float rowOne = yPadding;
    float rowTwo = DISPLAY_WIDTH / 3 + yPadding;
    float rowThree = DISPLAY_WIDTH / 3 * 2 + yPadding;

    float colOne = xPadding;
    float colTwo = xPadding + spaceForIcon;
    float colThree = DISPLAY_HEIGHT / 2 + spaceForIcon;
};