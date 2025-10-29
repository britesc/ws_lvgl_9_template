#include <Arduino.h>
#include "RP2040Support.h"
#include "actions.h"
#include "PicoFlashEeprom.h"
#include "vars.h"

void action_reboot(lv_event_t *e) {
    // TODO: Implement action reboot here
  	Serial.begin(115200);
  	while(!Serial);

	Serial.println("Rebooting...");	
	Serial.flush();
	rp2040.reboot();	
}

void action_update_zap_eeprom(lv_event_t *e) {
    // TODO: Implement action update_zap_eeprom here
	PicoFlashEeprom PFE((uint8_t)PICO_FLASH_EEPROM_SIZE);
  PFE.begin();
  PFE.writeZapNumber(get_var_textarea_zap_number());
}

