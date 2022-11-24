// #include "BLEDevice.h"
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

// //Default Temperature is in Celsius
// //Comment the next line for Temperature in Fahrenheit
// #define temperatureCelsius

// //BLE Server name (the other ESP32 name running the server sketch)
// #define bleServerName "3amouras_ESP32"

// /* UUID's of the service, characteristic that we want to read*/
// // BLE Service
// static BLEUUID bmeServiceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");

// // BLE Characteristics
// #ifdef temperatureCelsius
//   //Temperature Celsius Characteristic
//   static BLEUUID temperatureCharacteristicUUID("cba1d466-344c-4be3-ab3f-189f80dd7518");

// #endif

// // // Humidity Characteristic
// // static BLEUUID humidityCharacteristicUUID("ca73b3ba-39f6-4ab3-91ae-186dc9577d99");

// //Flags stating if should begin connecting and if the connection is up
// static boolean doConnect = false;
// static boolean connected = false;

// //Address of the peripheral device. Address will be found during scanning...
// static BLEAddress *pServerAddress;
 
// //Characteristicd that we want to read
// static BLERemoteCharacteristic* temperatureCharacteristic;
// // static BLERemoteCharacteristic* humidityCharacteristic;

// //Activate notify
// const uint8_t notificationOn[] = {0x1, 0x0};
// const uint8_t notificationOff[] = {0x0, 0x0};

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// //Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// //Variables to store temperature and humidity
// char* temperatureChar;
// // char* humidityChar;

// //Flags to check whether new temperature and humidity readings are available
// boolean newTemperature = false;
// // boolean newHumidity = false;

// //Connect to the BLE Server that has the name, Service, and Characteristics
// bool connectToServer(BLEAddress pAddress) {
//    BLEClient* pClient = BLEDevice::createClient();
 
//   // Connect to the remove BLE Server.
//   pClient->connect(pAddress);
//   Serial.println(" - Connected to server");
 
//   // Obtain a reference to the service we are after in the remote BLE server.
//   BLERemoteService* pRemoteService = pClient->getService(bmeServiceUUID);
//   if (pRemoteService == nullptr) {
//     Serial.print("Failed to find our service UUID: ");
//     Serial.println(bmeServiceUUID.toString().c_str());
//     return (false);
//   }
 
//   // Obtain a reference to the characteristics in the service of the remote BLE server.
//   temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
//   // humidityCharacteristic = pRemoteService->getCharacteristic(humidityCharacteristicUUID);

//   if (temperatureCharacteristic == nullptr) {
//     Serial.print("Failed to find our characteristic UUID");
//     return false;
//   }
//   Serial.println(" - Found our characteristics");
 
//   //Assign callback functions for the Characteristics
//   temperatureCharacteristic->registerForNotify(temperatureNotifyCallback);
//   return true;
// }

// //Callback function that gets called, when another device's advertisement has been received
// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//   void onResult(BLEAdvertisedDevice advertisedDevice) {
//     if (advertisedDevice.getName() == bleServerName) { //Check if the name of the advertiser matches
//       advertisedDevice.getScan()->stop(); //Scan can be stopped, we found what we are looking for
//       pServerAddress = new BLEAddress(advertisedDevice.getAddress()); //Address of advertiser is the one we need
//       doConnect = true; //Set indicator, stating that we are ready to connect
//       Serial.println("Device found. Connecting!");
//     }
//   }
// };
 
// //When the BLE Server sends a new temperature reading with the notify property
// static void temperatureNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
//                                         uint8_t* pData, size_t length, bool isNotify) {
//   //store temperature value
//   temperatureChar = (char*)pData;
//   newTemperature = true;
// }



// // function that prints the latest sensor readings in the LCD display
// void printReadings(){
  
//   lcd.clear();  
//   // display temperature
//   // lcd.setTextSize(1);
//   lcd.setCursor(0,0);
//   lcd.print("Temperature: ");
//   // lcd.setTextSize(2);
//   lcd.setCursor(0,10);
//   lcd.print(temperatureChar);
//   // lcd.setTextSize(1);
//   // lcd.cp437(true);
//   lcd.write(167);
//   // lcd.setTextSize(2);
//   lcd.print("Temperature:");
//   lcd.print(temperatureChar);
//   #ifdef temperatureCelsius
//     //Temperature Celsius
//     lcd.print("C");
//     Serial.print("C");
//   #endif

// //   // //display humidity 
// //   // display.setTextSize(1);
// //   // display.setCursor(0, 35);
// //   // display.print("Humidity: ");
// //   // display.setTextSize(2);
// //   // display.setCursor(0, 45);
// //   // display.print(humidityChar);
// //   // display.print("%");
// //   // display.display();
// //   // Serial.print(" Humidity:");
// //   // Serial.print(humidityChar); 
// //   // Serial.println("%");
// }

// void setup() {

//   lcd.begin();
//   lcd.clear();         
//   lcd.backlight();      // Make sure backlight is on
//   delay(100);
//   lcd.noBacklight();
//   delay(100);
//   lcd.backlight();  

  
//   // Print a message on both lines of the LCD.
//   lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
//   lcd.print("Hello world!");

//   lcd.clear();


//   delay(1000);
  
  
//   //Start serial communication
//   Serial.begin(115200);
//   Serial.println("Starting Arduino BLE Client application...");

//   //Init BLE device
//   BLEDevice::init("");
 
//   // Retrieve a Scanner and set the callback we want to use to be informed when we
//   // have detected a new device.  Specify that we want active scanning and start the
//   // scan to run for 30 seconds.
//   BLEScan* pBLEScan = BLEDevice::getScan();
//   pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//   pBLEScan->setActiveScan(true);
//   pBLEScan->start(30);
// }

// void loop() {
//   // If the flag "doConnect" is true then we have scanned for and found the desired
//   // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
//   // connected we set the connected flag to be true.
//   if (doConnect == true) {
//     if (connectToServer(*pServerAddress)) {
//       Serial.println("We are now connected to the BLE Server.");
//       //Activate the Notify property of each Characteristic
//       temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
//       connected = true;
//     } else {
//       Serial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
//     }
//     doConnect = false;
//   }
//   //if new temperature readings are available, print in the OLED
//   if (newTemperature){
//     newTemperature = false;
//     // printReadings();
//   }
//   // delay(1000); // Delay a second between loops.
//   // lcd. setCursor (0, 1);
//   //  // We write the number of seconds elapsed 
//   // lcd. print ( millis () / 1000);
//   // lcd. print ( "SECONDS" );
//   // delay (100);

// }

#include "BLEDevice.h"
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

/* Specify the Service UUID of Server */
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
/* Specify the Characteristic UUID of Server */
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                            uint8_t* pData, size_t length, bool isNotify)
{
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.println((char*)pData);
}

class MyClientCallback : public BLEClientCallbacks
{
  void onConnect(BLEClient* pclient)
  {
    
  }

  void onDisconnect(BLEClient* pclient)
  {
    connected = false;
    Serial.println("onDisconnect");
  }
};

/* Start connection to the BLE Server */
bool connectToServer()
{
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());
    
  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

    /* Connect to the remote BLE Server */
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

    /* Obtain a reference to the service we are after in the remote BLE server */
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr)
  {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");


  /* Obtain a reference to the characteristic in the service of the remote BLE server */
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr)
  {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic");

  /* Read the value of the characteristic */
  /* Initial value is 'Hello, World!' */
  if(pRemoteCharacteristic->canRead())
  {
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if(pRemoteCharacteristic->canNotify())
  {
    pRemoteCharacteristic->registerForNotify(notifyCallback);

  }

    connected = true;
    return true;
}
/* Scan for BLE servers and find the first one that advertises the service we are looking for. */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
 /* Called for each advertising BLE server. */
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    /* We have found a device, let us now see if it contains the service we are looking for. */
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID))
    {
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    }
  }
};


void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.print("Hi IoT");
  delay(100);

  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("ESP32-BLE-Client");



  /* Retrieve a Scanner and set the callback we want to use to be informed when we
     have detected a new device.  Specify that we want active scanning and start the
     scan to run for 5 seconds. */
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}


void loop()
{

  /* If the flag "doConnect" is true, then we have scanned for and found the desired
     BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
     connected we set the connected flag to be true. */
  if (doConnect == true)
  {
    if (connectToServer())
    { 
      lcd.clear();
      lcd.print("BLE Connected");
      delay(1000);
      Serial.println("We are now connected to the BLE Server.");
    } 
    else
    {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }

  /* If we are connected to a peer BLE Server, update the characteristic each time we are reached
     with the current time since boot */
  if (connected)
  {
    std::string newValue = pRemoteCharacteristic->readValue();
    // String newValue = "Time since boot: " + String(millis()/2000);
    // Serial.println("Setting new characteristic value to \"" + newValue.c_str() + "\"");
    
    lcd.clear();
          // Make sure backlight is on
    Serial.println(newValue.c_str());
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.setCursor(7,0);
    lcd.print(newValue.c_str());
    
    /* Set the characteristic's value to be the array of bytes that is actually a string */
    
    /* You can see this value updated in the Server's Characteristic */
  }
  else if(doScan)
  {
    lcd.clear();
    lcd.print("Searching ble");
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }
  
  delay(2000); /* Delay a second between loops */
}