#include "EEManager.h"

uint8_t EEManager::begin(uint8_t addr, uint8_t key) {
  _addr = addr;
  if ((uint16_t) EEPROM.length() == 0) {
    #if defined(ESP8266) || defined(ESP32)
      EEPROM.begin(_size);
    #endif
  }

  if (_addr + _length + 1 > (uint16_t) EEPROM.length()) {
    return 2;
  }

  _ready = 1;
  if (EEPROM.read(_addr + _length) != key) {
      EEPROM.write(_addr + _length, key);
      save();

      return 1;
  }

  read();

  return 0;
}

void EEManager::save() {
  if (!_ready) {
    return;
  }
       
  write(true);
}

void EEManager::read() {
  for (uint16_t i = 0; i < _length; i++) {
    _data[i] = EEPROM.read(_addr + i);
  }
}

void EEManager::reset() {
  write(false);
}
   
uint16_t EEManager::start() {
	return _addr;
}

uint16_t EEManager::end() {
	return _addr + _size;
}

uint16_t EEManager::next() {
	return _addr + _size + 1;
}

void EEManager::write(bool saveData) {
  #if defined(ESP8266) || defined(ESP32)
    for (uint16_t i = 0; i < _length; i++) {
      EEPROM.write(_addr + i, saveData ? _data[i] : 0);
    }

    EEPROM.commit();
  #else
    for (uint16_t i = 0; i < _length; i++) {
      EEPROM.update(_addr + i, saveData ? _data[i] : 0);
    }
  #endif
}