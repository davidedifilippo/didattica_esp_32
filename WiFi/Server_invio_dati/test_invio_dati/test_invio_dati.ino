/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

int incomingByte = 0;   // for incoming serial data

const char* ssid     = "";
const char* password = "";

const char* host = "";

// Use WiFiClient class to create TCP connections
WiFiClient client;

String temp_title = "temperatura=";
String temp;
float temperatura = 14; //Dati da inviare con il Wifi

  
void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
                }

  Serial.print("connecting to ");
  Serial.println(host);
  

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


 temp = temp_title + (float)temperatura;
 inviaDato();
  

 

   
  }
  




// Questo metodo tenta di connettersi al server e poi prova ad inviare i dati uno per volta
void inviaDato() {

  
  
  //Invia temperatura
  
  //prova a connetterti al server
  if (client.connect(host, 80)) {
    Serial.println("Connesso al server ...");
    
    client.println("POST /inserisci_dati.php HTTP/1.1"); 
                                                    
    
    client.println("Host: "); 
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(temp.length()); //Lunghezza dato
    Serial.println(temp); //Per debug
    Serial.println(temp.length()); //Per debug
    client.println();
    client.println(temp);
  } 
  else {
    //Se fallisce la connessione
    Serial.println("Connection failed");
    Serial.println("Disconnecting.");
    client.stop();
  }
  //Attendi 10 secondi e disconnetti il client
  delay(10000);
  client.stop();
  Serial.println("Automatically disconnected after 10 seconds.");
  Serial.println("Continua...");
  
  
/*stessa cosa per gli altri dati*/


}