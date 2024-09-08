#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  struct_message myData;
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();
}



void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //设置ESP8266角色：
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //注册接收回调
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  delay(5000);
  Serial.print("mac Address: ");
  Serial.println(WiFi.macAddress());  //打印mac地址
}