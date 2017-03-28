#include "ESP8266.h"

#define SSID        "Venizao" 
#define PASSWORD    "venizao123"
#define HOST_NAME   "www.baidu.com"
#define HOST_PORT   (80)

ESP8266 wifi(Serial1);
 
void setup()
{
    Serial1.begin(115200);
    Serial.begin(9600);
    Serial.print("setup begin\r\n"); 

    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());

    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");

        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
     if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop()
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id;

    //ESPERA RESPOSTA DO GET DO WIFI
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 200);
    
    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        
        String str = (char*)buffer; 
        int corta1 = str.indexOf(" ");
        int corta2 = str.indexOf(" ",corta1+1);
        String hook = str.substring(corta1+1,corta2);
        Serial.println("c1: "+((String)corta1)+" - c2 "+((String)corta2));
        Serial.println("hook: "+hook);

        /*DESENVOLVER PARA PEGAR PARAMETROS DEPOIS*/
        String apiRoot = "";
        if(hook.equals("/")){
           Serial.println("HOOK /");


            String apiRoot = 
                  String("HTTP/1.1 200 OK\r\n") +
                  "Content-Type: application/json\r\n" +
                  "Connection: close\r\n" +  // the connection will be closed after completion of the response
                   // "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
                  "\r\n" +
                  "{retorno : true}"
                  "\r\n";
          
           apiRoot.getBytes(buffer, apiRoot.length() + 1);
           len = apiRoot.length();
        }

        if(hook.equals("/temperatura")){
           Serial.println("HOOK /temperatura");

            const int LM35 = A0; // Define o pino que lera a saída do LM35
            float temperatura;
            temperatura =   (LM35 * 500) / 1023;
            String apiRoot = 
                  String("HTTP/1.1 200 OK\r\n") +
                  "Content-Type: application/json\r\n" +
                  "Connection: close\r\n" +  // the connection will be closed after completion of the response
                   // "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
                  "\r\n" +
                  "{temperatura : "+temperatura+"}"
                  "\r\n";
          
           apiRoot.getBytes(buffer, apiRoot.length() + 1);
           len = apiRoot.length();
           delay(2000);
        }
 
        
        if(wifi.send(mux_id, buffer, len)) {
            Serial.print("send back ok\r\n");
        } else {
            Serial.print("send back err\r\n");
        }
        
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("release tcp ");
            Serial.print(mux_id);
            Serial.println(" ok");
        } else {
            Serial.print("release tcp");
            Serial.print(mux_id);
            Serial.println(" err");
        }

    }
    
}
