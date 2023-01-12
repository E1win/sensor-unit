#pragma once

#include "Arduino.h"
#include <WiFi.h>
#include "ESPNowW.h"
#include "config.h"

class DataSender
{
public:
    DataSender();

    void Init();

    void SendStatus(int id, bool status);

    static bool dataReceived;

private:
    // MAC ADDRESS OF RECEIVER
    uint8_t receiver_mac[6] = RECEIVER_MAC_ADDRESS;

    // Structure to send data
    // Must match receiver structure
    typedef struct data_message
    {
        int id;
        bool status;
    } data_message;

    data_message myData;
};