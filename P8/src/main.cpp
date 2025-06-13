#include <Arduino.h>

#define MIDA_BUFFER 1024  
uint8_t dades_rebudes_uart0[MIDA_BUFFER];  
uint8_t dades_rebudes_uart2[MIDA_BUFFER];  

void setup() {  
  // Inicialitzem el monitor sèrie (UART0)  
  Serial.begin(115200);  // UART0 per comunicar-nos amb el PC  
  Serial.println("Iniciant la comunicació...");  

  // Configuració d'UART2 amb els pins GPIO16 (RXD2) i GPIO17 (TXD2)  
  const int PIN_RXD2 = 16;  
  const int PIN_TXD2 = 17;  
  Serial2.begin(115200, SERIAL_8N1, PIN_RXD2, PIN_TXD2);  

  // Confirmació que UART2 està operatiu  
  Serial.println("UART2 configurat i preparat per comunicar-se.");  
}  

void loop() {  
  // Llegim dades d'UART0 (RXD0) i les enviem a UART2 (TXD2)  
  if (Serial.available()) {  
    int longitud = Serial.readBytes(dades_rebudes_uart0, MIDA_BUFFER);  
    if (longitud > 0) {  
      Serial.println("Dades rebudes des d'UART0, enviant a UART2...");  
      Serial2.write(dades_rebudes_uart0, longitud);  
    }  
  }  

  // Llegim dades d'UART2 (RXD2) i les retornem a UART0 (TXD0)  
  if (Serial2.available()) {  
    int longitud = Serial2.readBytes(dades_rebudes_uart2, MIDA_BUFFER);  
    if (longitud > 0) {  
      Serial.println("Dades rebudes des d'UART2, retornant a UART0...");  
      Serial.write(dades_rebudes_uart2, longitud);  
    }  
  }  
}  