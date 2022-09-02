#ifndef _EEManager_h
  #define _EEManager_h
  #include <EEPROM.h>

  class EEManager
  {
    public:
      template <typename T> EEManager(T &data, size_t size) {
        _data = (uint8_t*) &data;
        _length = sizeof(T);
        _size = size;
      }

      uint8_t begin(uint8_t addr, uint8_t key);
      void save();
      void read();
      void reset();
	  
	  // address methods
	  uint16_t start();
	  uint16_t end();
	  uint16_t next();

    private:
      uint8_t *_data, _length, _addr;
      bool _ready = 0;
      size_t _size;

      void write(bool saveData);
  };
#endif