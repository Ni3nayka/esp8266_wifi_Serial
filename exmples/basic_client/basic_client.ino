#include <esp8266_wifi_Serial.h>          // подключаем библиотеку

void setup() {
  Serial.begin(115200);                   // запускаем монитор порта
  WifiSerial.begin();                     // запускаем на esp8266 клиент, подключаемся к wifi сервера для общения (с именем и паролем wifi по умолчанию), ВНИМАНИЕ: программа будет зациклена на этом моменте до подключения к заданной сети
}

void loop() {
  WifiSerial.println("Hello!");           // отправляем серверу "Hello!", если не подключены, то отправлено будет как только подключимся
  Serial.println(WifiSerial.readLine());  // выводим в монитор порта что получили от сервера
  delay(1000);                            // ждем 1 секунду
}
