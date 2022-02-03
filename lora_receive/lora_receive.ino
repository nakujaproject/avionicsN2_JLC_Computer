#include <SPI.h>
#include <LoRa.h>

#define ESP8266  // comment if you want to use the sketch on a Arduino board
//#define OLED        // comment if you do not have a OLED display

const long freq = 868E6;
const int SF = 12;
const long bw = 125E3;

int counter, lastCounter;

void setup() {
  Serial.begin(9600);
  Serial.println("---LoRa Receiver---");
#ifdef ESP8266
  LoRa.setPins(16, 17, 15); // set CS, reset, IRQ pin
#else
  LoRa.setPins(10, A0, 2); // set CS, reset, IRQ pin
#endif


  if (!LoRa.begin(freq)) {
    Serial.println("Starting LoRa failed!");

    while (1);
  }

  LoRa.setSpreadingFactor(SF);
  // LoRa.setSignalBandwidth(bw);
  Serial.println("LoRa Started");

  Serial.print("Frequency ");
  Serial.print(freq);
  Serial.print(" Bandwidth ");
  Serial.print(bw);
  Serial.print(" SF ");
  Serial.println(SF);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    String message = "";
    while (LoRa.available()) {
      message = message + ((char)LoRa.read());

      // logging code to capture the timestamp that the message was received
      
    }
    
    String rssi = "\"RSSI\":\"" + String(LoRa.packetRssi()) + "\"";
    String jsonString = message;
    jsonString.replace("xxx", rssi);

    int ii = jsonString.indexOf("Count", 1);
    String count = jsonString.substring(ii + 8, ii + 11);
    counter = count.toInt();
    if (counter - lastCounter == 0) Serial.println("Repetition");
    lastCounter = counter;


    sendAck(message);
    String value1 = jsonString.substring(8, 11);  // Vcc or heighth
    String value2 = jsonString.substring(23, 26); //counter
  }
}

void sendAck(String message) {
  int check = 0;
  for (int i = 0; i < message.length(); i++) {
    check += message[i];
  }
  // Serial.print("/// ");
  LoRa.beginPacket();
  LoRa.print(String(check));
  LoRa.endPacket();
  Serial.print(message);
  Serial.print(" ");
  Serial.print("Ack Sent: ");
  Serial.println(check);
}
