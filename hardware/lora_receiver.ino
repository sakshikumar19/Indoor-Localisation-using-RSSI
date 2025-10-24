#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_CS 18
#define LORA_RST 23
#define LORA_IRQ 26
#define BAND 868E6

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    Serial.println("LoRa Receiver Starting...");

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    if (!LoRa.begin(BAND))
    {
        Serial.println("Starting LoRa failed!");
        while (1)
            ;
    }

    Serial.println("LoRa Initialized Successfully!");
}

void loop()
{

    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
        Serial.print("Received packet: ");

        while (LoRa.available())
        {
            String incoming = LoRa.readString();
            Serial.print(incoming);
        }
        Serial.print("  | RSSI: ");
        Serial.println(LoRa.packetRssi());
        // Serial.println();
    }
}