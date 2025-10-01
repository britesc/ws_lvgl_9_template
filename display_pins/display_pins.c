#include "display_pins.h"

void display_pins() 
{
	Serial.print("SDA:        ");
	Serial.println(SDA);
	Serial.print("MOSI:       ");
	Serial.println(SDA / MOSI);
	Serial.print("MISO:       ");
	Serial.println(MISO);
	Serial.print("SCL / SCLK: ");
	Serial.println(SCL);
	Serial.print("CS / SS:    ");
	Serial.println(SS);
}