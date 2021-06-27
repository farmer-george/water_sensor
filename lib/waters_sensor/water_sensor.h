/* Water Sensor V1.0
   Documentation in README.md
*/
#include <Arduino.h>

const int WATER_SENSORS = 3;                                              // physical connected water sensors
const int WTR_SNSR_MAXREADTIME = 1000;                                    // time in ms sensor can be used
enum waterSensors { WTR_SNSR1, WTR_SNSR2, WTR_SNSR3 };                    // list of water sensors

// PUBLIC function declaration
void waterSensorInit(waterSensors sensor, int sensorPin, int powerPin);   // put this to the initialization routine (probably setup())
int waterSensorRead(waterSensors sensor);                                 // read raw value and store it in structure/array
bool isDry(waterSensors sensor, int threshold);                           // threshold between 0 .. 1023, below threshold isDry() is false
