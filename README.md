# Pràctica 8: Comunicació Sèrie (UART)
## Introducció
En aquesta pràctica estudiarem la comunicació sèrie asíncrona mitjançant el protocol **UART** (Universal Asynchronous Receiver Transmitter), àmpliament utilitzat en sistemes encastats i microcontroladors com l'**ESP32**.

Fins ara, hem fet servir **UART** en pràctiques anteriors per a la comunicació amb el monitor sèrie (per exemple, `Serial.println("...")`), però en aquesta ocasió aprofundirem en el seu funcionament a baix nivell, implementant una comunicació bidireccional entre **UART0 (PC)** i **UART2** de l'**ESP32**.

#### Objectius de la pràctica
- Entendre el funcionament de la comunicació **UART** en l'**ESP32**.

- Implementar un sistema d'"eco" entre **UART0** i **UART2**.

- Visualitzar l'intercanvi de dades entre terminals connectats via **UART**.

- Reconèixer la utilitat d'**UART** en connexions amb mòduls com **GPS** o **GPRS/GSM**.

### Exercici 1: Bucle de comunicació UART2
#### Descripció
Establim un bucle de comunicació on les dades rebudes pel terminal **UART0 (RXD0, connectat al PC)** s'envien a **UART2 (TXD2)**. Alhora, la informació rebuda per **UART2 (RXD2)** es retransmet de tornada al terminal **UART0**, fent que la comunicació sigui visible al monitor sèrie.

```c++
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
```

#### Exemple de sortida:
```
Iniciant la comunicació...  
UART2 configurat i preparat per comunicar-se.  
Dades rebudes des d'UART0, enviant a UART2...  
Dades rebudes des d'UART2, retornant a UART0...  
Hola món!
```  
## Conclusions
La pràctica ens ha permès comprendre i aplicar el funcionament del **UART** en microcontroladors com l'**ESP32**.

Hem configurat **UART2** per redirigir dades d'entrada i sortida, creant un bucle d'eco.

**UART** és essencial en aplicacions com la lectura de mòduls **GPS** o la connexió amb mòdems **GSM/GPRS**, demostrant la seva versatilitat en sistemes encastats.

