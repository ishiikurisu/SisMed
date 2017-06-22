#define LED 13
#define TERMOPAR (A0)
#define LM35 (A5)

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TERMOPAR, INPUT);
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

void loop()
{
    float lm35_measure = (4 * analogRead(LM35) * 100.0) / 1024;
    Serial.print(millis());
    Serial.print(" ");
    Serial.println(lm35_measure);
    delay(500);
}
