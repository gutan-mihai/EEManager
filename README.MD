# EEManager
Library to work with EEPROM in Arduino and ESP8266

# Structure
```cpp
// read data into variable by reference
// for esp8266 and esp32 need to indicate eeprom size
template <typename T> EEManager(T &data, size_t size);

// start to work with eeprom
// return codes:
// 0 - key matched, data is readed from eeprom
// 1 - key did not match (first run)
// 2 - error, there is not enough space
uint8_t begin(uint8_t addr, uint8_t key);

// save data to eeprom
void save();

// read data from eeprom to reference
void read();

// remove all data from eeprom
void reset();

// given start address in eeprom
uint16_t start();

// given end address in eeprom
uint16_t end();

// given next free address in eeprom
uint16_t next();
```

# Example
```cpp
#include <ESP8266WiFi.h>
#include <EEManager.h>

struct Data {
  char user[32] = "";
  char pass[32] = "";
};
Data data;

// create EEManager instance
EEManager memory(data, 512); // for ESP8266 and ESP32 needed to indicate eeprom size

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  // start memory
  byte status = memory.begin(0, 'd');

  /*
    Return codes:
    0 - key matched, data is readed from eeprom
    1 - key did not match (first run)
    2 - error, there is not enough space
  */
  Serial.println(status);

  strcpy(data.user, "username");
  strcpy(data.pass, "password");
  memory.save();
}

void loop() {
  // read from eeprom every 5 seconds and print data
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    memory.read();
    Serial.printf("User: %d\n", data.user);
    Serial.printf("Password: %d\n", data.pass);
    previousMillis = currentMillis;
  }
}
```