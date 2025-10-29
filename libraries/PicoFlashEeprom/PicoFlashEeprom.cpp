#include "PicoFlashEeprom.h"


// Static member initialisation
Stream* PicoFlashEeprom::_logStream = &Serial;
bool PicoFlashEeprom::_loggingEnabled =
#ifdef PICO_FLASH_EEPROM_ENABLE_LOGGING
    true;
#else
    false;
#endif
PicoFlashEeprom::LogLevel PicoFlashEeprom::_logLevel = LOG_DEBUG;

// Constructor
PicoFlashEeprom::PicoFlashEeprom(uint8_t size) : _size(size) {}
//PicoFlashEeprom::~PicoFlashEeprom();

void PicoFlashEeprom::begin() {
    EEPROM.begin(_size);
    log(LOG_INFO, F("Started Pico Flash Eeprom"));
}

bool PicoFlashEeprom::isEepromValid() {
  if ((int)EEPROM.read(_eeprom_address) != 74 && (int)EEPROM.read(_eeprom_address + 1) != 66) {
    log(LOG_INFO, F("NOT Equal to 74 or J and 66 or B"));
    return false;
  }
    log(LOG_INFO, F("Equal to 74 or J and 66 or B"));
    return true;
}

void PicoFlashEeprom::initializeEeprom() {
    for (int i = 0; i < _size; i++) {
      EEPROM.write(i, 0);
    }
    EEPROM.write(_eeprom_address, 74);
    EEPROM.write(_eeprom_address + 1, 66);
    log(LOG_INFO, F("Initialised Pico Flash Eeprom"));
}

char*  PicoFlashEeprom::getZapNumber() {
    static char buffer[7];  // 6 bytes + null terminator

    for (int i = 0; i < LENGTH_ZAP_NUMBER; i++) {
        buffer[i] = (char)EEPROM.read(_eeprom_address + START_ZAP_NUMBER + i);
    }
    buffer[LENGTH_ZAP_NUMBER] = '\0';   // ensure string is null-terminated
    log(LOG_INFO, F("Got Stored Zap Number"));

    return buffer;
}

bool PicoFlashEeprom::isZapNumberValid(const char *str) {
  // Must be exactly 6 characters
  if (strlen(str) != LENGTH_ZAP_NUMBER) {
    log(LOG_INFO, F("Zap Number NOT Required Number of Characters"));
    return false;
  }
  // Check first two are uppercase letters
  if (!isupper(str[0]) || !isupper(str[1])) {
    log(LOG_INFO, F("Zap Number NOT 2 Alpha Characters"));
    return false;
  }
  // Check last four are digits
  for (int i = 2; i < 6; i++) {
    if (!isdigit(str[i])) {
      log(LOG_INFO, F("Zap Number NOT 4 Numeric Characters"));
      return false;
    }

  }
    log(LOG_INFO, F("Zap Number IS Valid"));
    return true;

}

void PicoFlashEeprom::writeZapNumber(const char *str) {
    for (int i = 0; i < strlen(str); i++) {
      EEPROM.write(_eeprom_address + START_ZAP_NUMBER + i, isupper(str[i]));
    }
    log(LOG_INFO, F("Written Zap Pico Flash Eeprom"));
}


void PicoFlashEeprom::setLogger(Stream* stream) {
    _logStream = stream;
}

void PicoFlashEeprom::setLogLevel(LogLevel level) {
    _logLevel = level;
}

void PicoFlashEeprom::enableLogging(bool enable) {
    _loggingEnabled = enable;
}

void PicoFlashEeprom::log(LogLevel level, const __FlashStringHelper* msg) {
    if (!_loggingEnabled || !_logStream || level > _logLevel)
        return;

    // Print timestamp
    _logStream->print('[');
    _logStream->print(millis());
    _logStream->print(F(" ms] "));

    // Print log level
    switch (level) {
        case LOG_ERROR: _logStream->print(F("[ERROR] ")); break;
        case LOG_WARN:  _logStream->print(F("[WARN ] ")); break;
        case LOG_INFO:  _logStream->print(F("[INFO ] ")); break;
        case LOG_DEBUG: _logStream->print(F("[DEBUG] ")); break;
        default: break;
    }

    // Print message
    _logStream->println(msg);
}
