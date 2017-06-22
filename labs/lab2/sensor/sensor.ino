#include "./filters.h"
#define LED 13
#define TERMOPAR (A0)
#define LM35 (A5)

MEAN_FILTER mean_filter;
WINDOW_FILTER window_filter(10);
EXP_FILTER exp_filter(0.7);
double lm35_measure;

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TERMOPAR, INPUT);
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

void loop()
{
    lm35_measure = (4 * analogRead(LM35) * 100.0) / 1024;
    mean_filter.add(lm35_measure);
    window_filter.add(lm35_measure);
    exp_filter.add(lm35_measure);
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(mean_filter.get());
    Serial.print("\t");
    Serial.print(window_filter.get());
    Serial.print("\t");
    Serial.println(exp_filter.get());
    delay(500);
}
