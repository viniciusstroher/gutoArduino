

#include <doxygen.h>
#include <ESP8266.h>
#include <aREST.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#define SSID "Venizao"       
#define PASSWORD  "venizao123"

ESP8266 wifi(Serial1);
WiFiServer server(80);

aREST rest = aREST();
// Create an instance of the server


// Variables to be exposed to the API
int temperatura;
int luminosidade;
int pir;

int getTemperatura(String command);
int getLuminosidade(String command);
int getPir(String command);



void setup()
{
      Serial1.begin(115200);
      Serial.begin(9600);
      
      temperatura = 24;
      luminosidade = 40;
      pir = 1;
      rest.variable("temperatura",&temperatura);
      rest.variable("luminosidade",&luminosidade);
      rest.variable("pir",&pir);
      
      // Function to be exposed
      rest.function("getTemperatura",getTemperatura);
      rest.function("getLuminosidade",getLuminosidade);
      rest.function("getPir",getPir);

      //rest.set_id("13");
      //rest.set_name("esp8266");

      if (wifi.setOprToStation()) {
          Serial.print("to station ok\r\n");
      } else {
          Serial.print("to station err\r\n");
      }
  
      if (wifi.joinAP(SSID, PASSWORD)) {
          Serial.print("Join AP success\r\n");
          Serial.print("IP: ");       
          Serial.println(wifi.getLocalIP().c_str());
          server.begin();
      } else {
          Serial.print("Join AP failure\r\n");
      }
      
      Serial.print("setup end\r\n");
      
}


void loop()
{
        /*Serial.print("FW Version: ");
        Serial.println(wifi.getVersion().c_str());
        //no monitor usar 115000 para ver wifi
        if (wifi.setOprToStation()) {
          Serial.print("to station ok\r\n");
        } else {
          Serial.print("to station err\r\n");
        }
  
        if (wifi.joinAP(SSID, PASSWORD)) {
          Serial.print("Join AP success\r\n");
          Serial.print("IP: ");       
          Serial.println(wifi.getLocalIP().c_str());
        } else {
          Serial.print("Join AP failure\r\n");
        }*/

         WiFiClient client = server.available();
         Serial.println("available "+client);
         //rest.handle(client);
         Serial.println("API OK");
}

int getTemperatura(String command) {
  // Get state from command
  int state = command.toInt();
  //digitalWrite(6,state);
  return 1;
}
int getLuminosidade(String command) {
  // Get state from command
  int state = command.toInt();
  //digitalWrite(6,state);
  return 1;
}
int getPir(String command) {
  // Get state from command
  int state = command.toInt();
  //digitalWrite(6,state);
  return 1;
}
