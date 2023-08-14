#include "LedControl.h"
#include "binary.h"
 
/*
 * Conectar os pinos da Matriz de Led 8x8 no Arduino
 * DIN conecta ao pino 7
 * CLK conecta ao pino 9
 * CS conecta ao pino 8 
 * 
 * Conectar botão no pino 5 - usar resistor 10k no GND
 * Conectar buzzer - pino positivo na porta 12 e negativo no GND
*/

//LedControl lc=LedControl(DIN,CLK,CS,1); //1 max7219 
LedControl lc=LedControl(7,9,8,1); //1 max7219

int pinoSensorMovimento = 13; 
int pinoBotao = 5; 
int pinoBuzzer = 12;  //um eu liguei na 11
int resultado = 0;

// Definimos padrões binários para cada número do dado (1 a 6)
byte zero[] = {
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000};
 
byte um[] = {
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000000,
B00000000};
 
byte dois[] ={
B00000000,
B01100000,
B01100000,
B00000000,
B00000000,
B00000110,
B00000110,
B00000000};
 
byte tres[]={
B11000000,
B11000000,
B00000000,
B00011000,
B00011000,
B00000000,
B00000011,
B00000011};
 
byte quatro[]={
B00000000,
B01100110,
B01100110,
B00000000,
B00000000,
B01100110,
B01100110,
B00000000};
 
byte cinco[]={
B11000011,
B11000011,
B00000000,
B00011000,
B00011000,
B00000000,
B11000011,
B11000011};
 
byte seis[]={
B00000000,
B11011011,
B11011011,
B00000000,
B00000000,
B11011011,
B11011011,
B00000000};
 
void setup() {
  
  pinMode(pinoBotao, INPUT);
  pinMode(pinoSensorMovimento, INPUT);
  
  lc.shutdown(0,false);
 
  // Se o pino de entrada analógica 5 estiver desconectado, leia análogo aleatório
  // o ruído fará com que a chamada para randomSeed () gere
  // diferentes números de sementes cada vez que o programa/sketch é executado. 
  // randomSeed () irá então tornar a função random() aleatória.
  //randomSeed(analogRead(5)); 
  
  // Ajustamos o brilho da matriz de leds para um valor médio
  lc.setIntensity(0,7);
  
  // Limpamos o display
  lc.clearDisplay(0); 

  //define o pino 11 como saída
  pinMode(pinoBuzzer,OUTPUT);

  Serial.begin(9600);
}
 
void loop() {

  int valorSensorMovimento;
  
  if (digitalRead(pinoBotao)){
    Serial.println("botao");
    rolaDado();
  }

  valorSensorMovimento = digitalRead(pinoSensorMovimento);
  
  if (valorSensorMovimento == 0){
    Serial.println("sensor");
    rolaDado();
  }  

  delay(50);
}
 
void rolaDado(){
  //int resultado = 0;
  int tempoDadoRolando = random(10, 15);
  
  for(int i=0; i<tempoDadoRolando; i++){
    // A variável resultado vai assumir um valor entre 1 e 6
    resultado = random(1, 7); 
    mostraResultado(resultado);
    delay(100 + i * 10);
  }
  
  for(int i=0; i<2; i++){
    mostraResultado(0);
    delay(500);
    mostraResultado(resultado);
    delay(250);
  }

  for(int i=0; i<resultado; i++){
    /* Ligamos o buzzer com uma frequencia de 1500hz*/
    tone(pinoBuzzer,200);  
    delay(1000); 
    /*Em delay esperamos um segundo para avançar para a próxima linha*/
   
    noTone(pinoBuzzer);
    /*Desligamos o Buzzer*/
     
    delay(1000);
    /*Esperamos um segundo para finalizar o método*/    
  }
}
 
void mostraResultado(int resultado){
  if(resultado==0){
    lc.setRow(0,0,zero[0]);
    lc.setRow(0,1,zero[1]);
    lc.setRow(0,2,zero[2]);
    lc.setRow(0,3,zero[3]);
    lc.setRow(0,4,zero[4]);
    lc.setRow(0,5,zero[5]);
    lc.setRow(0,6,zero[6]);
    lc.setRow(0,7,zero[7]);
  }
  else if(resultado==1){
    lc.setRow(0,0,um[0]);
    lc.setRow(0,1,um[1]);
    lc.setRow(0,2,um[2]);
    lc.setRow(0,3,um[3]);
    lc.setRow(0,4,um[4]);
    lc.setRow(0,5,um[5]);
    lc.setRow(0,6,um[6]);
    lc.setRow(0,7,um[7]);
  }
  else if(resultado==2){
    lc.setRow(0,0,dois[0]);
    lc.setRow(0,1,dois[1]);
    lc.setRow(0,2,dois[2]);
    lc.setRow(0,3,dois[3]);
    lc.setRow(0,4,dois[4]);
    lc.setRow(0,5,dois[5]);
    lc.setRow(0,6,dois[6]);
    lc.setRow(0,7,dois[7]);
  }
  else if(resultado==3){
    lc.setRow(0,0,tres[0]);
    lc.setRow(0,1,tres[1]);
    lc.setRow(0,2,tres[2]);
    lc.setRow(0,3,tres[3]);
    lc.setRow(0,4,tres[4]);
    lc.setRow(0,5,tres[5]);
    lc.setRow(0,6,tres[6]);
    lc.setRow(0,7,tres[7]);
  }
  else if(resultado==4){
    lc.setRow(0,0,quatro[0]);
    lc.setRow(0,1,quatro[1]);
    lc.setRow(0,2,quatro[2]);
    lc.setRow(0,3,quatro[3]);
    lc.setRow(0,4,quatro[4]);
    lc.setRow(0,5,quatro[5]);
    lc.setRow(0,6,quatro[6]);
    lc.setRow(0,7,quatro[7]);
  }
  else if(resultado==5){
    lc.setRow(0,0,cinco[0]);
    lc.setRow(0,1,cinco[1]);
    lc.setRow(0,2,cinco[2]);
    lc.setRow(0,3,cinco[3]);
    lc.setRow(0,4,cinco[4]);
    lc.setRow(0,5,cinco[5]);
    lc.setRow(0,6,cinco[6]);
    lc.setRow(0,7,cinco[7]);
  }
  else if(resultado==6){
    lc.setRow(0,0,seis[0]);
    lc.setRow(0,1,seis[1]);
    lc.setRow(0,2,seis[2]);
    lc.setRow(0,3,seis[3]);
    lc.setRow(0,4,seis[4]);
    lc.setRow(0,5,seis[5]);
    lc.setRow(0,6,seis[6]);
    lc.setRow(0,7,seis[7]);
  }
}
