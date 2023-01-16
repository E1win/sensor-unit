#include "./Net/DataSender.h"

DataSender::DataSender()
{
}

void DataSender::Init()
{
    Serial.println("DataSender starting...");

    // Set WiFi mode to station
    WiFi.mode(WIFI_MODE_STA);

    WiFi.disconnect();

    int initResult = ESPNow.init();

    if (initResult != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    ESPNow.add_peer(receiver_mac);
}

void DataSender::SendData(
    int id,
    bool status,
    float temperature,
    float idealTemperature,
    float humidity,
    float idealHumidity)
{
    myData.id = id;
    myData.status = status;
    myData.temperature = temperature;
    myData.idealTemperature = idealTemperature;
    myData.humidity = humidity;
    myData.idealHumidity = idealHumidity;

    esp_err_t result = ESPNow.send_message(receiver_mac, (uint8_t *)&myData, sizeof(myData));
    if (result == ESP_OK)
    {
        Serial.println("Send with success!");
    }
    else
    {
        Serial.println("Error sending data.");
    }
}

void DataSender::SendStatus(int id, bool status)
{
    myData.id = id;
    myData.status = status;

    esp_err_t result = ESPNow.send_message(receiver_mac, (uint8_t *)&myData, sizeof(myData));
    if (result == ESP_OK)
    {
        Serial.println("Send with success!");
    }
    else
    {
        Serial.println("Error sending data.");
    }
}