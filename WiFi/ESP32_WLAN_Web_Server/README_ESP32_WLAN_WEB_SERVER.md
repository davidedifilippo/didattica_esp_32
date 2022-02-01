# WiFi WEB SERVER

Esiste la possibilità di impostare il modulo come un server WEB HTTP in ascolto sulla porta TCP 80 


### Attivazione modulo WiFi

La prima cosa da fare è includere la libreria di gestione del modulo WiFi del Chip ESP32

      #include "WiFi.h"

Da questo momento possiamo lavorare sul modulo WiFi del chip tramite la classe WiFi. 

### Libreria di gestione di un server WEB HTTP

Bisogna includere il codice che permette di instanziare, impostare, attivare un server WEB di tipo HTTP 

      #include <WebServer.h>

Da questo momento abbiamo a disposizione la classe WebServer.

### Impostazioni iniziali

Si instanzia un servizio di tipo WebServer in ascolto sulla porta 80:  

WebServer server(80);

Il server per il momento tuttavia è inattivo. 


Si imposta l'indirizzo IP del server:

            IPAddress local_ip(192, 168, 1, 10);

Si imposta la maschera di sottorete:

      IPAddress subnet(255, 255, 255, 0);

Si imposta il gateway di riferimento:

      IPAddress gateway(192, 168, 1, 10);


### Connessione al server


Qualsiasi dispositivo WIFI con un browser WEB (PC/Tablet/Cellullare con Chrome o affini) o dispositivo con software client HTTP può collegarsi al server HTTP dell'esp32. Ricevuta la pagina HTML sarà possibile interagire con il modulo esp32


### Numero e stato dei led

Si collegano due led di colore diverso, uno sul GPIO 26 ed uno sul GPIO 27:


uint8_t LED1pin = 26;
bool LED1status = LOW;

uint8_t LED2pin = 27;
bool B_LED2status = LOW;


## Setup

Si attiva la porta seriale di comunicazione per il debug dell'applicazione:

      Serial.begin(115200);

Si impostano i piedini GPIO26 e GPIO27 del microcontrollore come output:

      pinMode(R_LEDpin, OUTPUT);
      pinMode(B_LEDpin, OUTPUT);

Si registrano le funzioni da richiamare per ogni evento di interesse che il server registra nell'interazione con il client:  

  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);

Si attiva l'access point:

  WiFi.softAP(SSID, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

Si attiva il server:

      server.begin();
      Serial.println("HTTP server started");


## Loop

Ciclicamente si controlla se ci sono nuovi client connessi:

      server.handleClient();

Si controlla se si deve cambiare lo stato di uno dei led, per effetto di un evento (comando dal client) verificatosi nel frattempo:

  
      if (LED1status){
            digitalWrite(LED1pin, HIGH);
      }
      else{
            digitalWrite(LED1pin, LOW);
      }

      if (LED2status){
            digitalWrite(LED2pin, HIGH);
      }
      else{
            digitalWrite(LED2pin, LOW);
      }


## Funzioni di gestione eventi

Ad ogni evento che modifica lo stato delle cose aggiorno la pagina HTML e la invio al client:


      void handle_OnConnect() {
            LED1status = LOW;
            LED2status = LOW;
            Serial.println("GPIO26 Status: OFF | GPIO27 Status: OFF");
            server.send(200, "text/html", SendHTML(LED1status, LED2status));
      }

In questo caso il client si è appena connesso. Invio la pagina con lo stato attuale dei led.

      void handle_led1on() {
            LED1status = HIGH;
            Serial.println("GPIO26 Status: ON");
            server.send(200, "text/html", SendHTML(true, LED2status));
      }

In questo caso il client ha inciato ilcomando di accensione del led sul pin 26

      void handle_led1off() {
            LED1status = LOW;
            Serial.println("GPIO26 Status: OFF");
            server.send(200, "text/html", SendHTML(false, LED2status));
      }

In questo caso il client ha inciato il comando di spegnimento del led sul pin 26

      void handle_led2on() {
            LED2status = HIGH;
            Serial.println("GPIO27 Status: ON");
            server.send(200, "text/html", SendHTML(LED1status, true));
      }

In questo caso il client ha inciato ilcomando di accensione del led sul pin 26

      void handle_led2off() {
            LED2status = LOW;
            Serial.println("GPIO27 Status: OFF");
            server.send(200, "text/html", SendHTML(LED1status, false));
      }

In questo caso il client ha inciato il comando di spegnimento del led sul pin 26. In tutti gli altri casi:

      void handle_NotFound() {
      server.send(404, "text/plain", "Not found");
      }


## Aggiornamento della pagina HTML e invio al client 


            String SendHTML(uint8_t led1stat, uint8_t led2stat) {
            String ptr = "<!DOCTYPE html> <html>\n";
            ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
            ptr += "<title>LED Control</title>\n";
            ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
            ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
            ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
            ptr += ".button-on {background-color: #3498db;}\n";
            ptr += ".button-on:active {background-color: #2980b9;}\n";
            ptr += ".button-off {background-color: #34495e;}\n";
            ptr += ".button-off:active {background-color: #2c3e50;}\n";
            ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
            ptr += "</style>\n";
            ptr += "</head>\n";
            ptr += "<body>\n";
            ptr += "<h1>ESP32 Web Server</h1>\n";
            ptr += "<h3>Controllo accensione/spegnimento LED</h3>\n";

            if (led1stat){
            ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
            }
            else{
            ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
            }
            if (led2stat){
            ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
            }
            else
            {
            ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
            }

            ptr += "</body>\n";
            ptr += "</html>\n";
            return ptr;
            }