#include "./filters.h"
#define LED 13
#define TERMOPAR (A0)
#define LM35 (A5)

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

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TERMOPAR, INPUT);
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

void loop()
{
    // Measuring
    lm35_measure = (5 * analogRead(LM35) * 100.0) / 1024;
    thermocouple_measure = map(analogRead(TERMOPAR), 0, 1023, 0, 5000) /  1000.0;

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
