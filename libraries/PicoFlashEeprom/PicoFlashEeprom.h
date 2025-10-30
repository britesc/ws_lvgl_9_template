#ifndef PICO_FLASH_EEPROM_H
#define PICO_FLASH_EEPROM_H

#include <Arduino.h>
#include <EEPROM.h>


#define PICO_FLASH_EEPROM_SIZE 512
// Uncomment or define in your sketch to enable logging globally
//#define PICO_FLASH_EEPROM_ENABLE_LOGGING

class PicoFlashEeprom {
public:
    enum LogLevel {
        LOG_NONE  = 0,
        LOG_ERROR = 1,
        LOG_WARN  = 2,
        LOG_INFO  = 3,
        LOG_DEBUG = 4
    };

    // Const
    const uint8_t LENGTH_ZAP_NUMBER = 6;
    const uint8_t LENGTH_ZAP_NUMBER_BUFFER = LENGTH_ZAP_NUMBER + 1;
    const uint8_t START_ZAP_NUMBER = 2;

    // Constructor
    PicoFlashEeprom(uint8_t size);

    // Public methods
    void begin();
    bool isEepromValid();
    void initializeEeprom();
    char* getZapNumber();
    bool isZapNumberValid(const char *str);
    void writeZapNumber(const char *str);
		
    // Logging configuration
    static void setLogger(Stream* stream);
    static void setLogLevel(LogLevel level);
    static void enableLogging(bool enable);

private:
    uint8_t _size;
    uint8_t _eeprom_address = 0;

    // Static members for logging
    static Stream* _logStream;
    static bool _loggingEnabled;
    static LogLevel _logLevel;

    // Internal logging function
    static void log(LogLevel level, const __FlashStringHelper* msg);
};



#endif // PICO_FLASH_EEPROM_H
