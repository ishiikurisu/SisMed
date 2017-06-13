#define LED 13
#define MEAN_FILTER 1
#define WINDOW_FILTER 2
#define EXP_FILTER 3
#define TERMOPAR (A0)
#define LM35 (A5)

int HOW_MANY = -1;

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(TERMOPAR, INPUT);
    pinMode(LM35, INPUT);
    Serial.begin(9600);
}

void loop()
{

}

void serialEvent()
{
    String inlet = Serial.readString();

    if (inlet.startsWith("media")) {
        HOW_MANY = inlet.substring(5).toInt();
        readWithMean();
    }
    else if (inlet.startsWith("movel")) {
        HOW_MANY = inlet.substring(5).toInt();
        readWithWindowed();
    }
    else if (inlet.startsWith("exp")) {
        HOW_MANY = inlet.substring(3).toInt();
        readWithExp();
    }
}

float toVolts(int analog)
{
    return map(analog, 0, 1023, 0, 5000) / 1000.0;
}

// TODO Implement filters
void readWithMean()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        // TODO Convert analog values to voltage
        // TODO Apply filter
        Serial.print(micros());
        Serial.print(" ");
        Serial.print(toVolts(analogRead(TERMOPAR)));
        Serial.print(" ");
        Serial.print(toVolts(analogRead(LM35)));
        Serial.print(";");
    }

    Serial.println();
}

void readWithWindowed()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        // TODO Convert analog values to voltage
        // TODO Apply filter
        Serial.print(micros());
        Serial.print(" ");
        Serial.print(toVolts(analogRead(TERMOPAR)));
        Serial.print(" ");
        Serial.print(toVolts(analogRead(LM35)));
        Serial.print(";");
    }

    Serial.println();
}

void readWithExp()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        // TODO Convert analog values to voltage
        // TODO Apply filter
        Serial.print(micros());
        Serial.print(" ");
        Serial.print(toVolts(analogRead(TERMOPAR)));
        Serial.print(" ");
        Serial.print(toVolts(analogRead(LM35)));
        Serial.print(";");
    }

    Serial.println();
}
