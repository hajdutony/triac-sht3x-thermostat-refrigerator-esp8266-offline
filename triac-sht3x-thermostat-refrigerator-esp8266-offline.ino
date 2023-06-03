#include <Arduino.h>
#include <Wire.h>
#include <ArtronShop_SHT3x.h>

const int triacPin = 15;
int triacState = LOW;
ArtronShop_SHT3x sht3x(0x44, &Wire); // ADDR: 0 => 0x44, ADDR: 1 => 0x45

void setup() {
  pinMode(triacPin, OUTPUT);
  Serial.begin(115200);

  Wire.begin();
  while (!sht3x.begin()) {
    Serial.println("SHT3x not found !");
    delay(1000);
  }
}

void loop() {
  if (sht3x.measure()) {
    Serial.print("Temperature: ");
    Serial.print(sht3x.temperature(), 1);
    Serial.print(" *C\tHumidity: ");
    Serial.print(sht3x.humidity(), 1);
    Serial.print(" %RH");
    Serial.println();
  } else {
    Serial.println("SHT3x read error");
  }

    if (sht3x.temperature() > 9)  {
      triacState = HIGH;
    } 
    if (sht3x.temperature() < 6){
      triacState = LOW;
    }
    digitalWrite(triacPin, triacState);
    Serial.print("Triac state is ");
    Serial.println(triacState);
  delay(1000);
}
