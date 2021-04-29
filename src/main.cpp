#include <Arduino.h>
#include <SinricPro.h> 
#include <WiFiManager.h> 

#define BOTAO_RESET       2
#define BOTAO_INTERRUPTOR 0

WiFiManager wifiManager;

typedef struct {
  int pino;
  bool ultEstado;
  unsigned long ultIntervalo;
  unsigned int tempoEspera;
} botaoConfig_t;

botaoConfig_t botaoReset = {BOTAO_RESET, LOW, 0, 5000};
botaoConfig_t botaoInterruptor = {BOTAO_INTERRUPTOR, LOW, 0, 250};

void verificaBotao(botaoConfig_t *botao, void funcao(void)){
  bool estadoPino = digitalRead(botao->pino);
  if(estadoPino != botao->ultEstado){
    botao->ultEstado = estadoPino;
    botao->ultIntervalo = millis();
  }
    
  if((millis() - botao->ultIntervalo > botao->tempoEspera) && botao->ultEstado == LOW){
    funcao();
  } 
}

/*
*   Limpa as credenciais salvas do WiFi e reinicia o dispositivo.
*/
void resetaConfig(){
  Serial.println("Limpando credenciais");
  wifiManager.resetSettings();
  delay(1000);
  ESP.reset();
}

void setup() {
  Serial.begin(115200);
  pinMode(botaoReset.pino, INPUT_PULLUP);
  pinMode(botaoInterruptor.pino, INPUT_PULLUP);

  if(!wifiManager.autoConnect("AutoConnectAP")){
    Serial.println("Não conseguiu iniciar modo AP. Tentando novamente...");
    delay(1000);
    ESP.reset();
  }
}

void loop() {
  verificaBotao(&botaoReset, resetaConfig);
}