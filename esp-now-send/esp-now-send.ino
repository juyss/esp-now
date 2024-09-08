#include <ESP8266WiFi.h>
#include <espnow.h>
//对方MAC地址
uint8_t broadcastAddress[] = { 0x48, 0x55, 0x19, 0xC8, 0x60, 0xB8 };

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t status) {
  Serial.print("rnLast Packet Send Status:t");
  Serial.println(status == 0 ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  //与另一个ESP-NOW设备配对以发送数据
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  //打印mac地址
  Serial.print("mac Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // Set values to send
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1, 20);
  myData.c = 1.2;
  myData.d = "Hello";
  myData.e = false;

  // Send message via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  delay(3000);
}