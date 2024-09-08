#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("hello");  //加打印hello原因是模块刚上电有点乱码
}

void loop() {
  // put your main code here, to run repeatedly:
  //0x48, 0x55, 0x19, 0xC8, 0x60, 0xB8
  Serial.println(WiFi.macAddress());
  delay(1000);
}
