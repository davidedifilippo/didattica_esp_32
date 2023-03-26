 ## Include 
 
 Includo le librerie per la gestione del sensore tmp102   
   
    #include <Arduino.h>
    
 Per la gestione della comunicazione esp32 sensore tmp102:
    
    #include <Wire.h> 
 
 Per la gestione del sensore tmp102:   
 
    #include <SparkFunTMP102.h> 
    
 Per la connessione all'access point:
 
    #include <WiFiMulti.h>
    
 File da creare ed inserire nella cartella include del progetto con le credenziali di accesso all'AP:
    
    #include "secret.h"

Includo le librerie per la dichiarazione di un oggetto client per server InfluxDB:
    
    #include <InfluxDbClient.h>

Includo le librerie per la gestione della comunicazione con il server InfluxDB:

    #include <InfluxDbCloud.h>
 
 ## Dichiarazione delle variabili:
 
 Impongo un nome per identificare il sensore nella fase di ricezione dati:   
    
    #define DEVICE "ESP32_Aquilair_0"
    
  Creo un oggetto per la gestione della connessione WiFi all'AP:
 
    WiFiMulti wifiMulti;
  
  Creo un oggetto TMP102 per la gestione del sensore:
  
    TMP102 temp_sensor_tmp102;
    
 Creo una variabile per immagazzinare le letture:

    int temp = 0; 
    
 Dichiaro tutte le informazioni necessarie per collegarmi al database InfluxDB locale:
   
    #define INFLUXDB_URL "http://192.168.1.101:8086"         
    #define INFLUXDB_TOKEN "DaKS_0wlYhUOaIDNVuan8Xxk0jU6ETy6on_vIcXtjbHSH3aCnIXYQdbDvediSgoGwINsXGu0buUG7go1AJgkKA==" 
    #define INFLUXDB_ORG "burned_electron"        
    #define INFLUXDB_BUCKET "tmp102_data"       
    #define TZ_INFO "AEDT+11"                    //InfluxDB v2 timezone

Occorre naturalmente cambiare l'indirizzo IP locale.

Creo un oggetto client con le informazioni di connessione al server:

    InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);     //InfluxDB client instance with preconfigured InfluxCloud certificate
 
Creo un data point da poter inviare al server contenente un tag riconoscibile in ricezione:

    Point sensor("weather");   //Data point
 
 ## Fase di setup

      Serial.begin(9600);    
      Wire.begin();                                       

      if(!temp_sensor_tmp102.begin())
      {
        Serial.println("Il TMP102 non risponde.");
        Serial.println("Controllare la connessione al bus I2C. STOP ESECUZIONE.");
        while(1); 
       }
 

       WiFi.mode(WIFI_STA);                                              //Setup wifi connection
       wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

      Serial.print("Connecting to wifi");                               //Connect to WiFi
      while (wifiMulti.run() != WL_CONNECTED) 
      {
        Serial.print(".");
        delay(100);
      }
  
    Serial.println();

    sensor.addTag("device", DEVICE);                                   //Add tag(s) - repeat as required
    sensor.addTag("SSID", WIFI_SSID);

    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");                 //Accurate time is necessary for certificate validation and writing in batches

    if (client.validateConnection())                                   //Check server connection
    {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } 
    else 
    {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }

## Fase di Loop


      temp_sensor_tmp102.wakeup();
      temp = temp_sensor_tmp102.readTempC();                            //Record temperature
     temp_sensor_tmp102.sleep();                            
  

      sensor.clearFields();                                              //Clear fields for reusing the point. Tags will remain untouched

     sensor.addField("temperature", temp);                              // Store measured value into point
 

    
     if (wifiMulti.run() != WL_CONNECTED)                               //Check WiFi connection and reconnect if needed
        Serial.println("Wifi connection lost");

     if (!client.writePoint(sensor))                                    //Write data point
     {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
     }
  
      Serial.print("Temp: ");                                            //Display readings on serial monitor
       Serial.println(temp);
  
     delay(10000); 
