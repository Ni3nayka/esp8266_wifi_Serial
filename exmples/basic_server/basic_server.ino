#include <esp8266_wifi_Serial.h>          // подключаем библиотеку

void setup() {
  Serial.begin(115200);                   // запускаем монитор порта
  WifiSerial.begin("SERVER");             // запускаем на esp8266 сервер (с именем и паролем wifi по умолчанию)
}

void loop() {
  WifiSerial.println("Hello!");           // отправляем подключившемуся к нам устройству "Hello!", если никто не подключен, то отправлено будет как только кто-то подключится
  Serial.println(WifiSerial.readLine());  // выводим в монитор порта что получили от подключенного к нам устройства
  delay(1000);                            // ждем 1 секунду
}
