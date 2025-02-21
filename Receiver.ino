#include <esp_now.h>
#include <WiFi.h>

int ButtonA_Pin = ;
int ButtonB_Pin = ;
int Up_Pin = ;
int Down_Pin = ;
int Left_Pin = ;
int Right_Pin = ;

typedef struct struct_message {
  bool ButtonA, ButtonB, Up, Down, Right, Left;
} struct_message;

struct_message Data;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&Data, incomingData, sizeof(Data));

  Data.ButtonA = DigitalWrite(ButtonA_Pin);
  Data.ButtonB = DigitalWrite(ButtonB_Pin);
  Data.Up = DigitalWrite(Up_Pin);
  Data.Down = DigitalWrite(Down_Pin);
  Data.Right = DigitalWrite(Right_Pin);
  Data.Left = DigitalWrite(Left_Pin);
  
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  pinMode(ButtonA_Pin, INPUT);
  pinMode(ButtonB_Pin, INPUT);
  pinMode(Up_Pin, INPUT);
  pinMode(Down_Pin, INPUT);
  pinMode(Right_Pin, INPUT);
  pinMode(Left_Pin, INPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {

}
