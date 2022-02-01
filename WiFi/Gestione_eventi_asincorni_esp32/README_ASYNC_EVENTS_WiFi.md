# WiFi Async Events

Esiste la possibilità di registrare delle funzioni da eseguire quando si verifichino determinati eventi nella connessione WiFi. A

## Attivazione modulo WiFi

La prima cosa da fare è includere la libreria di gestione del modulo WiFi del Chip ESP32

      #include "WiFi.h"

Da questo momento possiamo lavorare sul modulo WiFi del chip tramite la classe WiFi. 

## Setup

Ovviamente si attiva il modulo di comunicazione seriale per eseguire il debug dell'applicazione. 

Serial.begin(115200);

In questo caso si imposta la velocità di comunicazione ad un valore più elevato, dato che il processore tensilica è a 32bit e la frequenza di clock è elevata (80MHz)

Si registrano i seguenti eventi asincroni, da gestire nel momento in cui si verificano (gestione asincrona):


            /*Registrazione degli eventi WIFI da gestire*/
            WiFi.onEvent(esp32_Connesso, SYSTEM_EVENT_STA_CONNECTED);
            WiFi.onEvent(IP_WiFi_Assegnato,SYSTEM_EVENT_STA_GOT_IP); 
            WiFi.onEvent(StazioneWiFiDisconnessa, SYSTEM_EVENT_STA_DISCONNECTED);
            /*fine*/

Bisogna poi richimare la funzione che si occupa della connessione al router dell'es32:

             void connetti_Alla_Rete_Wifi() {
                  Serial.println("Tentativo di connessione all’access point WiFi... "); 
                  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            }


### event = SYSTEM_EVENT_STA_CONNECTED

In questo caso si registra la funzione:

            void esp32_Connesso(WiFiEvent_t event, WiFiEventInfo_t info) { 
                  Serial.println("Evento WiFi:" + SYSTEM_EVENT_STA_CONNECTED); 
            } 


### event = SYSTEM_EVENT_STA_GOT_IP

Quando l'esp32 ha ottenuto l'indirizzo IP dal router richiamo l'evento di gestione:

            void IP_WiFi_Assegnato(WiFiEvent_t event, WiFiEventInfo_t info){ 
            Serial.print("WiFi connesso a ");
            Serial.print("WIFI_SSID");
            Serial.print("Indirizzo IP esp32: "); 
            Serial.println(WiFi.localIP()); 
      } 

### event = SYSTEM_EVENT_STA_DISCONNECTED

Se l'esp32 si dovesse disconnettere dal router possiamo richiamare l'evento di gestione:

            void StazioneWiFiDisconnessa(WiFiEvent_t event, WiFiEventInfo_t info) { 
                  Serial.println("Disconnesso dall’AP WiFi "); 
                  Serial.print("connessione WiFi persa. Motivo: "); 
                  Serial.println(info.disconnected.reason); 
                  Serial.println("Provo a riconnettermi: "); 
                  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
            } 
         

## Loop

Nel loop non sono previste operazioni 

delay(1000);


