#include "./filters.h"
#define LED 13
#define TERMOPAR (A0)
#define LM35 (A5)

MEAN_FILTER mean_filter;
WINDOW_FILTER window_filter(10);
EXP_FILTER exp_filter(0.7);
MEAN_FILTER thermocouple_mean;
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
    lm35_measure = (4 * analogRead(LM35) * 100.0) / 1024;
    thermocouple_measure = map(analogRead(TERMOPAR), 0, 5000, 0, 1023) /  1000.0;

    // Filtering
    mean_filter.add(lm35_measure);
    thermocouple_mean.add(thermocouple_measure);

    // Writting output
    Serial.print(millis());
    Serial.print(";");
    Serial.print(mean_filter.get());
    Serial.print(";");
    Serial.println(thermocouple_mean.get(), 5);
    delay(500);
}
