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
    float xPosTemp = 10;
    float xPosHumidity = DISPLAY_HEIGHT / 2 + 10;
    float yPos = 10;

    m_sprite.drawString("Temp:", xPosTemp, yPos);
    m_sprite.drawString("Hmdty:", xPosHumidity, yPos);

    yPos += 30;

    m_sprite.drawString(String(temperature) + "C", xPosTemp, yPos);
    m_sprite.drawString(String(humidity) + "%", xPosHumidity, yPos);

    yPos += 30;

    m_sprite.drawString("Ideal:", xPosTemp, yPos);
    m_sprite.drawString("Ideal:", xPosHumidity, yPos);

    yPos += 30;

    m_sprite.drawString(String(idealTemperature) + "C", xPosTemp, yPos);
    m_sprite.drawString(String(idealHumidity) + "%", xPosHumidity, yPos);

    m_sprite.pushSprite(0, 0);
}