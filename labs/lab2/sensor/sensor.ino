#include "./filters.h"
#define LED 13
#define TERMOPAR (A0)
#define LM35 (A4)

/* ######################
   # PHYSICAL FUNCTIONS #
   ###################### */

// Convert the voltage read from a K type thermocouple to celsius degrees
// based on the reading of a LM35 sensor in volts.
double convert_to_temperature(double termopar, double lm35)
{
   double lm35_1 = lm35 * 100;
   double lm35_2 = lm35_1 * lm35_1;
   double lm35_3 = lm35_2 * lm35_1;
   double lm35_4 = lm35_3 * lm35_1;

   // Polinomio gerado pela interpolação da tebela disponível em: http://sensorestemperatura.com.br/Fotos_pdf/TABELA%20K%201.pdf
   double cold_voltage = 0.001455643972886 + 0.039088035432556 * lm35_1 + 0.000038064028883 * lm35_2 - 0.000000240144827 * lm35_3 + 0.000000000449283 * lm35_4;

   double termopar_1 = 1000 * termopar/500 + cold_voltage; // unidade em milivolts
   double termopar_2 = termopar_1 * termopar_1;
   double termopar_3 = termopar_2 * termopar_1;
   double termopar_4 = termopar_3 * termopar_1;
   double termopar_5 = termopar_4 * termopar_1;

   return -0.037834437781076 + 25.552551420040750 * termopar_1 - 0.570291877969017 * termopar_2 + 0.088906098929135 * termopar_3 - 0.004173887396488 * termopar_4 + 0.000006005013885 * termopar_5;
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
    lm35_measure = analogRead(LM35) * 5.0 / 1024;
    thermocouple_measure = convert_to_temperature(analogRead(TERMOPAR)*5.0/1024/50, lm35_measure);
    lm35_measure = lm35_measure * 100;

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
