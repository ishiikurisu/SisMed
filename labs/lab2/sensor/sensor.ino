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

// TODO Implement filters
void readWithMean()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        Serial.print(millis());
        Serial.print(" ");
        Serial.print(analogRead(TERMOPAR));
        Serial.print(" ");
        Seria.print(analogRead(LM35));
        Serial.print(";");
    }

    Serial.println();
}

void readWithWindowed()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        Serial.print(millis());
        Serial.print(" ");
    }

    Serial.println();
}

void readWithExp()
{
    for (int i = 0; i < HOW_MANY; ++i)
    {
        Serial.print(millis());
        Serial.print(" ");
    }

    Serial.println();
}
