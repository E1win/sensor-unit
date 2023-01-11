#include "./App.h"

App::App() : m_ptnmtr(POTENTIOMETER_PIN),
             m_dht11(DHT_PIN, DHT_TYPE)
{
}

void App::Run()
{
    Serial.begin(9600);

    while (!Serial)
    {
    };

    Serial.println("Starting program...");

    while (true)
    {

        Serial.println(m_dht11.GetTemperature());

        // use buttons to change temperature

        // update temperature

        // update humidity

        // check if alarm is supposed to go off
        // store result in newState bool
        // check if currentState is different from previousState
        // if so,
        //   send update to Hub Unit with new state
        //   send the Alarm class the new state
        //      (which is running on a separate proto-thread)
        //   update State.

        // Optimisation: create new protothread when alarm is supposed to turn on
        // and just delete it when alarm is supposed to turn off
    }
}