#include "DHT.h"
// #include "MQ135.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>



#define bleServerName "3amouras_ESP32"


BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


#define DHTTYPE DHT11
#define DHTPIN 32
#define productionPIN 27
#define buzzerTHPIN 14
#define CO2PIN 2
const int lightPin = 15;
int turnOnPL;




DHT dht(DHTPIN, DHTTYPE);
// MQ135 gasSensor = MQ135(CO2PIN);


void setup() {

  turnOnPL = 0;  //turn on production light set to 0 as a default
  pinMode(productionPIN, OUTPUT);
  pinMode(buzzerTHPIN, OUTPUT);
  Serial.begin(115200);
  dht.begin();
   Serial.begin(115200);
  Serial.println("Starting BLE Server!");
BLEDevice::init("ESP32-BLE-Server");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE
);
 pCharacteristic->setValue("Hello, World!");
  pService->start();
//BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
BLEDevice::startAdvertising();
//pAdvertising->start();
  Serial.println("Characteristic defined! Now you can read it in the Client!");

}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)
  int lightIntensity = analogRead(lightPin);
  // float CO2 = gasSensor.getPPM();
  int CO2 = analogRead(CO2PIN);

  //   if (isnan(h) || isnan(t)) {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }

  if (lightIntensity >= 1600) {
    turnOnPL = 1;  // low light
  } else {
    turnOnPL = 0;
  }
  digitalWrite(productionPIN, turnOnPL);

  if (CO2 > 600) {
    tone(buzzerTHPIN, 8000);  // Send 4KHz sound signal...
    delay(1000);
    noTone(buzzerTHPIN);  // Stop sound...
  }
  if ((t > 32) && (h > 30)) {
    tone(buzzerTHPIN, 1000);  // Send 2KHz sound signal...
    delay(1000);
    noTone(buzzerTHPIN);  // Stop sound...
  }

    // std::string value = pCharacteristic->getValue();
    
    char sz[20] = {' '} ;

    int val_int = (int) t;   // compute the integer part of the float

    float val_float = (abs(t) - abs(val_int)) * 100;

    int val_fra = (int)val_float;

    sprintf (sz, "%d.%d", val_int, val_fra); //

    pCharacteristic->setValue(sz);    
    Serial.print("The new characteristic value is: ");
    Serial.println(sz);
    delay(2000);




  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("\nLight Intensity: "));
  Serial.println(lightIntensity);
  Serial.print(F("\nCO2: "));
  Serial.print(CO2);
  Serial.println(" ppm");
  // delay(1000);

  
}




