#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

const char* ssid ="";
const char* password = "";


#define RETRY_LIMIT  20

int rtl = RETRY_LIMIT;

void setup()
{ 
    Serial.begin(115200);
    WiFi.begin(ssid,password);
    while (WiFi.status()!= WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP Address");
    Serial.println(WiFi.localIP()); 
 
}

void loop()
{
    float h = 50;
    float t = 40;
    float p = 30;

    delay(500);

    
  
    //Open a connection to the server
      HTTPClient http;

      http.begin("http://192.168.1.149/esp_get.php");

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    //format your POST request.
    //SensorName,location,Tempraure,Humidity,Pressure

      int httpResponseCode = http.POST("&temp=10&hum=20&probe=4&charge=2&device=1");

      if (httpResponseCode >0){
          //check for a return code - This is more for debugging.
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      }
      else{
        Serial.print("Error on sending post");
        Serial.println(httpResponseCode);
      }
    //closde the HTTP request.
      http.end(); 
    //Monitor values in console for debugging.
    
   //wait 1 minutes for next reading
    delay(10000);
}
