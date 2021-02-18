#include <Arduino.h>
#include <WiFi.h>
#include "AsyncUDP.h"
#include "Adafruit_GFX.h"
#include "DotFlippersMatrix.h"

// constants
const char* ssid = "xxxxx";
const char* password = "xxxxx";

// global vars
DotFlippersMatrix dotFlippersMatrix = DotFlippersMatrix(35, 30);
WiFiServer wifiServer(81);
AsyncUDP udp;

void setupUDP(){
  if(udp.listen(1234)) {
    Serial.print("UDP Listening.");
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      //reply to the client
      packet.printf("Got %u bytes of data", packet.length());
    });
  }
}

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {

        case SYSTEM_EVENT_STA_START:
            WiFi.setHostname("FipDots");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            Serial.println("STA connected");
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.println("STA got IP");
            Serial.print("STA SSID: ");
            Serial.println(WiFi.SSID());
            Serial.print("STA IPv4: ");
            Serial.println(WiFi.localIP());
            Serial.print("MAC address: ");
            Serial.println(WiFi.macAddress());

            wifiServer.begin();
            setupUDP();
            
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.print("STA Disconnected. ");
            Serial.println(info.disconnected.reason);
            WiFi.persistent(false);
            WiFi.disconnect(true);
            ESP.restart();
            break;
        default:
            break;
    }
}
void connectWiFi() {
    WiFi.persistent(false);
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_STA);

    WiFi.onEvent(WiFiEvent);
    WiFi.begin(ssid, password);
    Serial.println(F("WiFi connexion ongoing"));
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }
  delay(1000); 

  dotFlippersMatrix.setDisplayPixelSize(24,14);
  dotFlippersMatrix.setViewOrigin(0,10);
  dotFlippersMatrix.begin();

  dotFlippersMatrix.clear(0x00);
  dotFlippersMatrix.display();
  delay(1000);
  dotFlippersMatrix.clear(0x01);
  dotFlippersMatrix.display();
  delay(1000);

  connectWiFi();
  delay(1000);


  

}

int count = 0;
int frameCount=0;

void loop() {

  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
       
      while (client.available()>0) {
        char c = client.read();
        // Serial.print(c, HEX);
        // Serial.print(' ');
        dotFlippersMatrix.getDisplayBuffer()[count] = c;
        count++;
        if (count>47) {
          count = 0;
          Serial.println(frameCount++);
          dotFlippersMatrix.flushDisplayBuffer();
          delay(30);
        } 
      }
 
      delay(30);
    }
    client.stop();
    Serial.println("\nClient disconnected\n");
    count = 0;
    frameCount = 0;
  }


}
  // for (int i=0; i<31; i++) {
  //   delay(20);
  //   dotFlippersMatrix.clear(0x00);
  //   dotFlippersMatrix.drawChar(i, 10, 0x30+countPrevious, 0x01, 0x00, 2);
  //   dotFlippersMatrix.display();
  // }
  // for (int i=0; i<9; i++) {
  //   delay(20);
  //   dotFlippersMatrix.clear(0x00);
  //   dotFlippersMatrix.drawChar(0, 18-i, 0x30+countNext, 0x01, 0x00, 2);
  //   dotFlippersMatrix.display();
  // }
  // countPrevious = countNext;
  // if (countNext > 74) countNext = 0;
