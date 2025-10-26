#include <Arduino.h>
#include <water_sensor.h>

struct waterSensorData {
    // index of waterSensor is array index itself
    int sensorPin;
    int powerPin;
    int value;
    unsigned long t0 = 0;
};

waterSensorData waterSensorArray[WTR_ENDMARK];

// PRIVATE function declaration
int sensorValue(waterSensors sensor);

// PUBLIC function definition

int getMaxWaterSensors()
{
    return WTR_ENDMARK;
}

void waterSensorInit(waterSensors sensor, int sensorPin, int powerPin)
{
    waterSensorArray[sensor].sensorPin = sensorPin;
    waterSensorArray[sensor].powerPin = powerPin;
    waterSensorArray[sensor].value = 0;
    pinMode(sensorPin, INPUT);
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);        // start with sensor off
}

int waterSensorRead(waterSensors sensor)
{
    unsigned long ms = millis();
    if (ms - waterSensorArray[sensor].t0 >= WTR_SNSR_MAXREADTIME) {
        waterSensorArray[sensor].t0 = ms;
        waterSensorArray[sensor].value = sensorValue(sensor);
        return waterSensorArray[sensor].value;
    } else {
        return waterSensorArray[sensor].value;
    }
}

bool isDry(waterSensors sensor, int threshold)
{
    return waterSensorRead(sensor) < threshold;
}

// PRIVATE function definition

int sensorValue(waterSensors sensor)
{
    int value;
    // 1) switch the power of the sensor on
    // 2) read the #value of the water sensor
    // 3) switch the power off
    // 4) return the measured value
    digitalWrite(waterSensorArray[sensor].powerPin, HIGH);
    value = analogRead(waterSensorArray[sensor].sensorPin);
    digitalWrite(waterSensorArray[sensor].powerPin, LOW);
    return value;
} // sensorValue()
