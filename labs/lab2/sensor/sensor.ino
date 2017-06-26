#include "./filters.h"
#define LED 13
#define TERMOPAR (A0)
#define LM35 (A5)

/* ######################
   # PHYSICAL FUNCTIONS #
   ###################### */

// Convert the voltage read from a K type thermocouple to celsius degrees
// based on the reading of a LM35 sensor in celsius.
double convert_to_temperature(double thermocouple, double ref_temp)
{
    return (thermocouple * 0.08) - ref_temp;
}


/* ################
   # MAIN PROGRAM #
   ################ */

/* Filter selection */
// MEAN_FILTER lm35_filter;
// MEAN_FILTER thermocouple_filter;
WINDOW_FILTER lm35_filter(10);
WINDOW_FILTER thermocouple_filter(10);
// EXP_FILTER lm35_filter(0.7);
// EXP_FILTER thermocouple_filter(0.7);
// KALMAN_FILTER lm35_filter;
// KALMAN_FILTER thermocouple_filter;
double lm35_measure;
double thermocouple_measure;

// Setting Arduino up
void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TERMOPAR, INPUT);
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

// Writes on the serial port a comma separated value string
// relating the time, the lm35 filtered measure and the
// thermocouple measure
void loop()
{
    // Measuring
    lm35_measure = (5 * analogRead(LM35) * 100.0) / 1024;
    thermocouple_measure = convert_to_temperature(analogRead(TERMOPAR), lm35_measure);

    // Filtering
    lm35_filter.add(lm35_measure);
    thermocouple_filter.add(thermocouple_measure);

    // Writting output
    Serial.print(millis());
    Serial.print(";");
    Serial.print(lm35_filter.get());
    Serial.print(";");
    Serial.println(thermocouple_filter.get(), 5);
    delay(500);
}
