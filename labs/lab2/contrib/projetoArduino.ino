#define QUANT_DADOS 101 // maior ou igual a 'N + 1'. Onde 'N' é maior 'n' da fórmula da média móvel símples utilizado. No caso, mediaMovelSimples_100 utiliza n = 100.
#define termoparPIN A2
#define lm35PIN A1

double calculaTemperatura(double termopar, double lm35);
double calculaMedia(double valor, double media, int posicao);
double calculaMediaMovelSimples(double valor, double media, int tamanho, int leitura);
double calculaMediaMovelPonderada(double valor, double media, double alpha);
void filtroKalman(double* x, double A, double H, double Q, double R, double* P, double z);
void comunicacaoSerial();

/* Variáveis Globais (utilizadas em loop()) */
  int leitura = 0;
  
  double termopar;
  double lm35;
  double temperatura;
  
  double media = 0;
  double mediaMovelPonderada_09 = 0;
  double mediaMovelPonderada_07 = 0;
  double mediaMovelPonderada_05 = 0;
  
  double mediaMovelSimples_20 = 0;         // Dados do último segundo. (usa-se delay(50))
  double mediaMovelSimples_100 = 0;        // Dados dos últimos 5 segundos.
  double vetor_medicoes[QUANT_DADOS];
  
  double mediaKalman = 25;
  double incertezaKalman =  1;

/** Inicialização do Arduíno **/
void setup() {
  Serial.begin(9600);                                       // Abre comunicação do Arduíno com PC. 9600bps
}

/** Loop Infinito (main) **/
void loop() {
  termopar = (double) analogRead(termoparPIN);              // Lê valor do potenciômetro
  lm35 = (double) analogRead(lm35PIN);                      // Lê valor do lm35
  
  termopar = termopar*5/1023;                               // Converte para volts
  lm35 = lm35*5/1023;                                       // Converte para volts

  /*Serial.print(lm35);
  Serial.print(",");
  Serial.println(termopar);*/
  
  temperatura = calculaTemperatura(termopar, lm35);
  
  leitura++;
  
  media = calculaMedia(temperatura, media, leitura);
  mediaMovelSimples_20 = calculaMediaMovelSimples(temperatura, mediaMovelSimples_20, 20, leitura);
  mediaMovelSimples_100 = calculaMediaMovelSimples(temperatura, mediaMovelSimples_100, 100, leitura);
  mediaMovelPonderada_09 = calculaMediaMovelPonderada(temperatura, mediaMovelPonderada_09, 0.9);
  mediaMovelPonderada_07 = calculaMediaMovelPonderada(temperatura, mediaMovelPonderada_07, 0.7);
  mediaMovelPonderada_05 = calculaMediaMovelPonderada(temperatura, mediaMovelPonderada_05, 0.5);
  filtroKalman(&mediaKalman, 1, 1, 0.1, 2.2, &incertezaKalman, temperatura);
  
  comunicacaoSerial();
}

/** Calcula Temperatura **/
double calculaTemperatura(double termopar, double lm35){
   lm35 = lm35 * 100;   // Conversão de volts para ºC
   double lm35_2 = lm35 * lm35;
   double lm35_3 = lm35_2 * lm35;
   double lm35_4 = lm35_3 * lm35;
   
   // Polinomio gerado pela interpolação da tebela disponível em: http://sensorestemperatura.com.br/Fotos_pdf/TABELA%20K%201.pdf
   double tensao_fria = 0.001455643972886 + 0.039088035432556 * lm35 + 0.000038064028883 * lm35_2 - 0.000000240144827 * lm35_3 + 0.000000000449283 * lm35_4;
   
   double tensao_quente = 1000 * termopar/506 + tensao_fria; // unidade em milivolts
   double tensao_quente_2 = tensao_quente * tensao_quente;
   double tensao_quente_3 = tensao_quente_2 * tensao_quente;
   double tensao_quente_4 = tensao_quente_3 * tensao_quente;
   double tensao_quente_5 = tensao_quente_4 * tensao_quente;
   
   return -0.037834437781076 + 25.552551420040750 * tensao_quente - 0.570291877969017 * tensao_quente_2 + 0.088906098929135 * tensao_quente_3
          - 0.004173887396488 * tensao_quente_4 + 0.000006005013885 * tensao_quente_5;
}

/** Calcula a média **/
double calculaMedia(double valor, double media, int posicao){
  return (posicao-1)*media/posicao + valor/posicao;
}

/** Calcula a média móvel **/
double calculaMediaMovelSimples(double valor, double media, int tamanho, int leitura){
  vetor_medicoes[(leitura-1) % QUANT_DADOS] = valor;
  if(leitura > tamanho){
    return media + (valor-vetor_medicoes[(leitura-1-tamanho) % QUANT_DADOS])/tamanho;
  }else{
    return calculaMedia(valor, media, leitura); 
  }
}

/** Calcula a média móvel ponderada **/
double calculaMediaMovelPonderada(double valor, double media, double alpha){
  return alpha*media + (1-alpha)*valor;
}

void filtroKalman(double* x, double A, double H, double Q, double R, double* P, double z){
  double K;
  double xp;
  double Pp;
  
  //etapa de predicao
  xp = A*(*x);
  Pp = A*(*P)*A + Q;

  //etapa de correcao
  K = Pp*H/(H*Pp*H + R);
  (*x) = xp + K*(z - H*xp);
  (*P) = Pp - K*H*Pp;
}

/** Envia valores pela porta serial **/
void comunicacaoSerial(){
  Serial.print(lm35*100);
  Serial.print(",");
  Serial.print(temperatura);
  Serial.print(",");
  Serial.print(media);
  Serial.print(",");
  Serial.print(mediaMovelSimples_20);
  Serial.print(",");
  Serial.print(mediaMovelSimples_100);
  Serial.print(",");
  Serial.print(mediaMovelPonderada_09);
  Serial.print(",");
  Serial.print(mediaMovelPonderada_07);
  Serial.print(",");
  Serial.print(mediaMovelPonderada_05);
  Serial.print(",");
  Serial.println(mediaKalman);
  
  
  delay(50);
}

void pausa();
void reseta();

void serialEvent(){
  String valor = Serial.readStringUntil('\n');
  if(valor == "PAUSE"){
    pausa();
  }else if(valor == "PAUSE_RESET"){
    reseta();
    pausa();
  }
}

void pausa(){
  String valor = "";
  while(valor != "START"){
    delay(50);
    valor = Serial.readStringUntil('\n');
    if(valor == "PAUSE_RESET"){
      reseta();
    }
  }
}

void reseta(){
  leitura = 0;
  media = 0;
  mediaMovelSimples_20 = 0;
  mediaMovelSimples_100 = 0;
  mediaMovelPonderada_09 = 0;
  mediaMovelPonderada_07 = 0;
  mediaMovelPonderada_05 = 0;
  mediaKalman = 25;
  incertezaKalman = 1;
}

