
#include <esp_now.h>
#include <Wifi.h>

int ButtonA_Pin = ;
int ButtonB_Pin = ;
int Up_Pin = ;
int Down_Pin = ;
int Left_Pin = ;
int Right_Pin = ;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message {
  bool ButtonA, ButtonB, Up, Down, Right, Left;
} struct_message;

struct_message Data;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
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

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  Data.ButtonA = DigitalRead(ButtonA_Pin);
  Data.ButtonB = DigitalRead(ButtonB_Pin);
  Data.Up = DigitalRead(Up_Pin);
  Data.Down = DigitalRead(Down_Pin);
  Data.Right = DigitalRead(Right_Pin);
  Data.Left = DigitalRead(Left_Pin);
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &Data, sizeof(Data));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(10);
}
