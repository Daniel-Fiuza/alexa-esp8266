#include <Arduino.h>
#include <SinricPro.h> 
#include <WiFiManager.h> 

#define BOTAO_RESET 2
#define BOTAO_INTERRUPTOR 0

typedef struct {
  int pino;
  bool ultEstado;
  unsigned long ultIntervalo;
} botaoConfig_t;

botaoConfig_t botaoReset = {BOTAO_RESET, LOW, 0};
botaoConfig_t botaoInterruptor = {BOTAO_INTERRUPTOR, LOW, 0};

void verificaBotao(botaoConfig_t *botao, unsigned int tempoEspera, void funcao(void)){
  bool estadoPino = digitalRead(botao->pino);
  if(estadoPino != botao->ultEstado){
    botao->ultEstado = estadoPino;
    botao->ultIntervalo = millis();
  }
    
  if((millis() - botao->ultIntervalo > tempoEspera) && botao->ultEstado == LOW){
    funcao();
  } 
}

void teste(){
  Serial.println("Testando");
}

void setup() {
  pinMode(botaoReset.pino, INPUT_PULLUP);
  pinMode(botaoInterruptor.pino, INPUT_PULLUP);
}

void loop() {
  verificaBotao(&botaoReset, 5000, teste);
}