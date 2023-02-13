# WiFi Scan

Il programma consente la scansione della rete Wifi 802.11 b/g/n alla ricerca di punti di accesso LAN. Per visualizzare i risultati
della scansione viene utilizzato per semplicità il monitor seriale. 

## Attivazione modulo WiFi

La prima cosa da fare è includere la libreria di gestione del modulo WiFi del Chip ESP32

      #include "WiFi.h"

Da questo momento possiamo lavorare sul modulo WiFi del chip tramite la classe WiFi. 

## Setup

Imopstiamo il modulo di comunicazione seriale dell'esp32 per il debug del firmware:

      Serial.begin(9600);

Per poterci associare ad una rete locale dobbiamo impostare il modulo in modalità STATION o stazione (l'altra modalità possibile è AP o access point). 


      WiFi.mode(WIFI_STA);
      
Disconnettiamo il dispositivo da qualsiasi punto di accesso precedentemente acquisito:    

 
      WiFi.disconnect();
      delay(100);

Il setup dell'esp32 è terminato: 
  
      Serial.println("Setup terminato");

## Loop

Il metodo scanNetworks() applicato all'oggetto WiFi restituisce il numero di reti WiFi locali raggiungibili dal modulo in quel momento:

      int n = WiFi.scanNetworks();

dove n è il numero di reti WiFi locali trovate. Comunichiamo che la scansione è terminata: 

      Serial.println("Scansione terminata...");

Stampiamo il numero di access point rilevati. Se n == 0:

      Serial.println("Nessun access point disponibile"); 
  
 altrimenti:
 
    Serial.print(n);
    Serial.println(" reti trovate");
  
Possiamo determinare l'identificativo di rete univoco SSID  (Service Set Identifier) i-esimo tra gli n possibili tramite:

      WiFi.SSID(i);

Il livello di potenza RSSI (Received Signal Strenght Indicator) del segnale ricevuto dalla i-esima stazione in decibel 
per milliWatt può essere ricavato tramite la chiamata:

      WiFi.RSSI(i);

Il tipo di algoritmo di criptazione utilizzato per la sicurezza delle informazioni scambiate può essere ricavato tramite:

      WiFi.encryptionType(i);

Se le informazioni dovessero viaggiare in chiaro la chiamata resituisce il valore enumerativo WIFI_AUTH_OPEN.

       for (int i = 0; i < n; ++i) { // Print SSID and RSSI for each network found
                                          
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            }
    
 Aspettiamo 5 secondi prima di una nuova scansione:
 
            delay(5000)

