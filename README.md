# QwiicSoilMoistureSensor

## How to use

```cpp
#include <Arduino.h>

#include <../lib/soil/QwiicSoilMoistureSensor.h>

static SoilMoistureSensor *_soil;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Initializing");
  _soil = new SoilMoistureSensor();
  _soil->begin();
  Serial.println("Starting");
}

void loop() {
  Serial.println("LED on and start read soil");
  _soil->ledOn();
  uint16_t soilADC = _soil->readSoil();
  Serial.print("Readout result: ");
  Serial.println(soilADC);
  Serial.println("LED off");
  _soil->ledOff();
  delay(10000);
}
```

**TODO** Write more information.