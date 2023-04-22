/*
 * arduino library for solving problems with graphs:
 * https://github.com/Ni3nayka/esp8266_wifi_Serial
 *
 * links:
 * server:
 * https://diytech.ru/projects/sozdanie-veb-servera-esp8266-kod-i-skhemy
 * https://www.embedded-robotics.com/esp8266-wifi/
 * client:
 * https://robotzero.one/sending-data-esp8266-to-esp8266/
 *
 * author: Egor Bakay <egor_bakay@inbox.ru>
 * write:  April 2023
 * modify: April 2023
 */

#pragma once

#include <ESP8266WiFi.h>

#define WIFI_NAME_DEFAULT "uzKoQOg02HYQacJUQGX2"
#define WIFI_PASSWORD_DEFAULT "3XnoFOYwxYZv3DP9sM0X"
#define WIFI_MODE_SERVER "SERVER"
#define WIFI_MODE_CLIENT "CLIENT"
#define WIFI_MODE_DEFAULT WIFI_MODE_CLIENT
#define WIFI_MAX_CONNECTIONS_DEFAULT 1

WiFiServer my_server(80);
      
class myWifiSerial {
    public:
      void begin(String mode=WIFI_MODE_DEFAULT,String wifi_name=WIFI_NAME_DEFAULT,String wifi_password=WIFI_PASSWORD_DEFAULT,int max_connections=WIFI_MAX_CONNECTIONS_DEFAULT) {
        myWifiSerial::mode = mode;
        myWifiSerial::wifi_name = wifi_name;
        myWifiSerial::wifi_password = wifi_password;
        myWifiSerial::max_connections = max_connections;
        if (myWifiSerial::mode==WIFI_MODE_SERVER) {
          if(!WiFi.softAP(myWifiSerial::wifi_name,myWifiSerial::wifi_password,1,false,myWifiSerial::max_connections)) {
            Serial.println();
            Serial.println();
            Serial.println("ERROR: error start wifi server");
            Serial.println();
          }
          my_server.begin();
        }
        else {
          delay(10);
          WiFi.mode(WIFI_STA);
          WiFi.begin(myWifiSerial::wifi_name, myWifiSerial::wifi_password);
          while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
          }
          Serial.println("OK");
        }
      }
      String get_wifi_name() { return myWifiSerial::wifi_name; }
      String get_wifi_password() { return myWifiSerial::wifi_password; }
      String get_wifi_mode() { return myWifiSerial::mode; }
      int get_wifi_max_connections() { return myWifiSerial::max_connections; }
      
    private:
      String wifi_name, wifi_password, mode, path;
      int max_connections;
      WiFiClient client;

      void update() {
        if (myWifiSerial::mode==WIFI_MODE_SERVER) {
          if (!myWifiSerial::client) {
            myWifiSerial::client = my_server.available();
          }
        }
        else {
          if (!myWifiSerial::client.connect("192.168.4.1", 80)) {
            Serial.println("connection failed");
            return;
          }
        }
      }
};

myWifiSerial WifiSerial;
