# WiFi Scan

Il programma consente la scasione della rete Wifi 802.11 b/g/n alla ricerca di punti di accesso LAN. Per visualizzare i risultati
della scansione viene utilizzato per semplicità il monitor seriale. 

## Attivazione modulo WiFi

La prima cosa da fare è includere la libreria di gestione del modulo WiFi del Chip ESP32

      #include "WiFi.h"

Da questo momento possiamo lavorare sul modulo WiFi del chip tramite la classe WiFi. 

## Setup

Per poterci associare ad una rete locale 
dobbiamo impostare il modulo in modalità STATION o stazione (l'altra modalità possibile è AP o access point). Nel setup:

      WiFi.mode(WIFI_STA);

## Loop

Il metodo scanNetworks() applicato all'oggetto WiFi restituisce il numero di reti raggiungibili dal modulo in quel momento:

int n = WiFi.scanNetworks();

dove n è il numero di reti WiFi locali trovate. Possiamo determinare l'identificativo di rete univoco SSID 
(Service Set Identifier) i-esimo tra gli n possibili tramite:

WiFi.SSID(i);

Il livello di potenza RSSI (Received Signal Strenght Indicator) del segnale ricevuto dalla i-esima stazione in decibel 
per milliWatt può essere ricavato tramite la chiamata:

WiFi.RSSI(i);

Il tipo di algoritmo di criptazione utilizzato per la sicurezza delle informazioni scambiate può essere ricavato tramite:

WiFi.encryptionType(i);

Se le informazioni dovessero viaggiare in chiaro la chiamata resituisce il valore enumerativo WIFI_AUTH_OPEN.



