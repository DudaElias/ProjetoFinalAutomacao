const int s0 = 9;
const int s1 = 10;
const int s2 = 13;
const int s3 = 12;
const int out = 11;

int ehVermelho = 1;
int ehVerde = 2;
int ehAzul = 3;
int ehMarrom = 4;
int ehLaranja = 5;
int ehAmarelo = 6;

int contarVerm;
int contarVerd;
int contarA;
int ultimaCor = 0;
int SemCor = 0;

int vermelho = 0;
int verde = 0;
int azul = 0;

int mediaVerm=0;
int mediaVerd=0;
int mediaA=0;

int mediaRR=0;
int mediaBR=0;
int mediaGR=0;

int mediaRG=0;
int mediaBG=0;
int mediaGG=0;

int mediaRB=0;
int mediaBB=0;
int mediaGB=0;

#include <Servo.h>
Servo servo;
int pinoSensor = 8; 

void setup() 
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  servo.attach(7);  // porta do servo
  Serial.begin(9600);
  delay(500);
  calibraSensor();
  //tempo = ultimaVez = diferenca = 0;
}                                                                                                                                                                           

int IdentificaCor()
{
  //verifica se a cor e verde
  if( (azul>(mediaBG-15) && azul<(mediaBG+15)) && (vermelho>(mediaRG-15) && vermelho<(mediaRG+15)) && (verde>(mediaGG-15) && verde<(mediaGG+15)))
    return ehVerde;
    
  //verifica se a cor e azul
  else if((azul>(mediaBB-15) && azul<(mediaBB+15)) && (vermelho>(mediaRB-15) && vermelho<(mediaRB+15)) && (verde >(mediaGB-15) && verde<(mediaGB+15)) )
    return ehAzul;
  
  //Verifica se a cor e vermelha  
  else if((azul>(mediaBR-15) && azul<(mediaBR+15)) && (vermelho>(mediaRR-15) && vermelho<(mediaRR+15)) && (verde >(mediaGR-15) && verde<(mediaGR+15)) )
    return ehVermelho;
  }
void loop()
{
  
  int CorIdentificada;
  Readcolor();
  CorIdentificada = IdentificaCor();

  //Verifica se a cor vermelha foi detectada  
  if (CorIdentificada == ehVermelho)  
  {  
       if(ultimaCor != ehVermelho)
         contarVerm++;
       ultimaCor = ehVermelho;
  }  
  
  //Verifica se a cor azul foi detectada  
  else if (CorIdentificada == ehAzul)   
  {  
       if(ultimaCor != ehAzul)
         contarA++;
       Serial.print(" Cor Identificada: Azul - Contador:");  
       Serial.print(contarA,'DEC');
       delay(10);
       ultimaCor = ehAzul;
  }  

  //Verifica se a cor verde foi detectada  
  else if (CorIdentificada == ehVerde)  
  {         
        if(ultimaCor != ehVerde)
             contarVerd++;
             
       Serial.print(" Cor Identificada: Verde Contador: ");  
       Serial.print(contarVerd,'DEC');
       delay(10);   
       ultimaCor = ehVerde; 
  }  
  
  else
  {
    Serial.print(" Cor Identificada: Nenhuma ");  
  }
    
    delay(2000);
    calibraSensor();
}
void Readcolor()  
{  
  //le saida com filtro vermelho
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  delay(50);
  vermelho = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  
  //Le saida com filtro azul
  digitalWrite(s3, HIGH);  
  delay(50);
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  //le saida com filtro verde
  digitalWrite(s2, HIGH);  
  delay(50);
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  
  /*
  Serial.print(" Leitura do sensor por filtro: "); 
  Serial.println(); 
  Serial.print(" Azul : ");  
  Serial.print(blue, DEC); 
  Serial.print(" Vermelho :");  
  Serial.print(red, DEC);  
  Serial.print(" Verde : ");  
  Serial.print(green, DEC); 
  Serial.println();  */
}


void calibraSensor()
{
  int i;
        mediaVerm = mediaA = mediaVerd = 0;
        for(i=0; i<20; i++)
        {
          Readcolor();
          mediaVerm +=vermelho;
          mediaA +=azul;
          mediaVerd += verde;
          delay(50);
        }
       
        mediaRR = mediaVerm/20;
        mediaBR = mediaA/20;
        mediaGR = mediaVerd/20;
        mediaVerm = mediaA = mediaVerd = 0;
        for(i=0; i<20; i++)
        {
          Readcolor();
          mediaVerm += vermelho;
          mediaA += azul;
          mediaVerd += verde;
          delay(50);
        }
       
        mediaRB = mediaVerm/20;
        mediaBB = mediaA/20;
        mediaGB = mediaVerd/20;
        mediaVerm = mediaA = mediaVerd = 0;
        for(i=0; i<20; i++)
        {
          Readcolor();
          mediaVerm += vermelho;
          mediaA += azul;
          mediaVerd += verde;
          delay(50);
        }
       
        mediaRG = mediaVerm/20;
        mediaBG = mediaA/20;
        mediaGG = mediaVerd/20;
}



