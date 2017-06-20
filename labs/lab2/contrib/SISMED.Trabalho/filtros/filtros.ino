#define termopar A0
#define LM A1
#define N 5  // para media movel
#define OP 3 //op = 1(Media),2(Mmovel),3(Mponderada) e 4(KF)


int V1,V2; //analog read retorna inteiro de 0 a 1023 (0 a 5v)
float V;  // valor medido
float Vk; // valor filtrado
float T,val1,val2;
float aux1,aux2=0; //aux1 = V(k-1)
int k = 1;
float data[N];
float alpha=0.7; // 0 < alpha < 1

void setup() {
  pinMode(termopar,INPUT);
  pinMode(LM,INPUT);
  
  Serial.begin(9600);  
}


void loop() {

  V1 = analogRead(LM);
  V2 = analogRead(termopar);
  
  val1 = float(V1*5)/1023; //do lm35
  val2 = (float(V2*5)/1023);   //tira ganho do amplificador

  T = (val1+val2)*0.025132*1000;
  
  Serial.println(T);

  switch(OP){
    case 1:
      if(k==1){
        aux1=V;
        Serial.println(T);
      }else{      
        Vk = (aux1/k)*(k-1) + T/k;
        Serial.println(Vk);
        aux1 = Vk;
      }
      break;
      
    case 2:
      if(k<=N){
        data[k-1]=T;
        aux1=T;
        Vk=aux1;
        Serial.println(Vk);
      }
      else{
        Vk = aux1 + (T-data[0])/N;
        Serial.println(Vk);
        reordena(T);
        aux1=Vk;   
      }
      break;
      
    case 3:
      if(k==1){
        aux1=T;
        Serial.println(T);
      }
      else{      
        Vk = aux1*alpha + T*(1-alpha);
        Serial.println(Vk);
        aux1 = Vk;
      }      
      break;
      
    case 4:
      
      break;
      
    default:
      break;
    }
  
  k=k+1;
  delay(500);
}

void reordena(float number){
  int i;
  for(i=0;i<(N-1);i++){
    data[i]=data[i+1];      
  }
  data[N-1]=number;
}