#include <Arduino.h>

#include "./App.h"

App app;

void setup()
{
  app.Run();
}

void loop()
{
  // Delay for 100ms to give IDLE task time to execute.
  delay(100);
}