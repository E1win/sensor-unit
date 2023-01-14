#include "./Interface/Display.h"

Display::Display() : m_tft(DISPLAY_WIDTH, DISPLAY_HEIGHT),
                     m_sprite(&m_tft)
{
}

void Display::Init()
{
    m_tft.init();

    m_tft.setRotation(1);
    m_tft.setTextDatum(MC_DATUM);

    m_sprite.createSprite(DISPLAY_HEIGHT, DISPLAY_WIDTH);

    Reset();
}

void Display::Reset()
{
    m_tft.fillScreen(TFT_BLACK);
    m_tft.setTextSize(2);
    m_tft.setTextColor(TFT_WHITE);

    m_sprite.setTextSize(2);
    m_sprite.fillRect(0, 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, TFT_BLACK);
    m_sprite.pushSprite(0, 0);
}

void Display::Update(float temperature, float idealTemperature, float humidity, float idealHumidity)
{
    // ROW 1

    m_sprite.drawString(String(UNIT_ID), colOne, rowOne);
    m_sprite.drawString("Huidig", colTwo, rowOne);
    m_sprite.drawString("Gewenst", colThree, rowOne);

    // DIVIDING LINE ROW 1 - ROW 2
    m_sprite.drawLine(0, rowTwo - yPadding, DISPLAY_HEIGHT, rowTwo - yPadding, TFT_WHITE);

    // DIVIDING LINE ROW 2 - ROW 3
    m_sprite.drawLine(0, rowThree - yPadding, DISPLAY_HEIGHT, rowThree - yPadding, TFT_WHITE);

    // DIVIDING LINE COL 1 - COL 2
    m_sprite.drawLine(colTwo - xPadding, 0, colTwo - xPadding, DISPLAY_WIDTH, TFT_WHITE);

    // ROW 2

    m_sprite.drawString("C", colOne, rowTwo);
    m_sprite.drawString(String(temperature) + "C", colTwo, rowTwo);
    m_sprite.drawString(String(idealTemperature) + "C", colThree, rowTwo);

    // ROW 3

    m_sprite.drawString("RV", colOne, rowThree);
    m_sprite.drawString(String(humidity) + "%", colTwo, rowThree);
    m_sprite.drawString(String(idealHumidity) + "%", colThree, rowThree);

    m_sprite.pushSprite(0, 0);
}