/* Water Sensor V1.0
   Documentation in README.md
*/
#include <Arduino.h>

const int WTR_SNSR_MAXREADTIME = 1000;                                    // time in ms sensor can be used
enum waterSensors {WTR_SNSR1,     // ADD or remove sensors here
                   WTR_SNSR2,
                   WTR_SNSR3,
                   WTR_ENDMARK }; // Leave WTR_ENDMARK as last entry

// PUBLIC function declaration

/*! Returns the amount of configured water sensors.

   @param void
   @return value of WTR_ENDMARK
*/
int getMaxWaterSensors();

/*! Initializes the water sensors.

    Use init preferred in setup().

    Note! If the used driver (transistor, MOSFET etc.) ic capable to
    supplie more then one sensor then this can be configured by using
    the same GPIO for all sensors. Means powerPin is identical.

    @param sensor is one of the Sensors in enum waterSensors
    @param sensorPin the pin where this sensor is connected to
    @param powerPin the pin which supplies the sensor with power
*/
void waterSensorInit(waterSensors sensor, int sensorPin, int powerPin);

/*! Returns the value of the addressed sensor.

    Sensor is one of the sensors defined in enum waterSensors.
    The value at an 10bit AVR ADC is between 0 and 1023.
    0 means no moisture at all.

    @param sensor the addressed sensor to get a value from
    @return value of the sensor between 0 and 1023
*/
int waterSensorRead(waterSensors sensor);

/*! Returns weather the sensor is supposed to be dry or wet.
    
    This function performs a simple comparision.
    Sensor values higher than the threshold are supposed to be wet.
    Sensor values below the threshold are supposed to be dry.
    You can find "good" values by reading the values and then
    calibrating the threshold to you needs.

    @param threshold value to define when it should deliver "dry"
    @return bool dry == true !dry means "wet"
*/
bool isDry(waterSensors sensor, int threshold);
