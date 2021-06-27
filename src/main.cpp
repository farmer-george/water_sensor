#include <Arduino.h>
#include <water_sensor.h>

unsigned long ms, t0 = 0;         // used for timing 
unsigned long msdelay = 1000;     // output should happen once a second
int threshold = 500;              // threshold to decide if "soil" is wet or dry
                                  // 500 works fine in many szenarios
int n = 0;                        // iteration counter

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Serial ready");

  // GPIO definition for water sensors
  // The power switch in this setup is done by one transistor at A0
  waterSensorInit(WTR_SNSR1, A1, A0);
  waterSensorInit(WTR_SNSR2, A2, A0);
  waterSensorInit(WTR_SNSR3, A3, A0);
}

void loop() {
  if ((ms = millis()) > (t0 + msdelay)) {                 // run code only msdelay milliseconds
    t0 = ms;                                              // remember start time of the run
    Serial.print(++n);                                    // count how often code is run
    Serial.print(": ");
    for (int i = 0; i < WATER_SENSORS; ++i) {             // iterate through all sensors
      Serial.print(" Sensor: ");
      Serial.print(i);
      if (isDry(waterSensors(i), threshold)) {            // ask if water sensor reports "dry"
        Serial.print(" = dry ");
      } else {
        Serial.print(" = wet ");
      }
      Serial.print("Value = ");
      Serial.print(waterSensorRead(waterSensors(i)));     // print the raw value which was measured
    }
    Serial.println();
  }
}
