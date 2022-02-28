#include <Arduino.h>

#include <Wire.h> 
#include <SparkFunTMP102.h> // Used to send and recieve specific information from our sensor


TMP102 sensor0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  
  if(!sensor0.begin())
  {
    Serial.println("Il TMP102 non risponde.");
    Serial.println("Controllare la connessione al bus I2C. STOP ESECUZIONE.");
    while(1); 
  }
  
}
 
void loop()
{
  float temperature;
  
 
  sensor0.wakeup();
  temperature = sensor0.readTempC();
  sensor0.sleep();

  // Print temperature and alarm state
  Serial.println("Temperature: ");
  Serial.print(temperature);
  

  delay(1000);  // Wait 1000ms
}
