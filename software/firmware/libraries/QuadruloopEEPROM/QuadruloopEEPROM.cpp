#include <QuadruloopEEPROM.h>
#include <EEPROM.h>

namespace QuadruloopEEPROM
{
	void loadConfig(uint8_t n, uint8_t centers[])
	{
#if defined(ESP8266_PERI_H_INCLUDED)
	EEPROM.begin(1024);
#endif
		// read first byte, see if it equals our "magic" value
		// if not, then we've never saved values to EEPROM, so just use defaults
		uint8_t m = EEPROM.read(EEPROM_MAGIC_ADDR);
		if (m == EEPROM_MAGIC) {
			Serial.println(F("Loading servo centers..."));
			for (uint8_t i = 0; i < n; i++) {
				centers[i] = EEPROM.read(EEPROM_CENTERS_ADDR + i);
				Serial.print(i);
				Serial.print(':');
				Serial.println((int)centers[i]);
			}
		} else {
			Serial.println(F("No stored settings, using defaults"));
		}
	}

	void saveConfig(uint8_t n, uint8_t centers[])
	{
#if defined(ESP8266_PERI_H_INCLUDED) || defined(ARDUINO_ARCH_ESP32)
		// update magic
		EEPROM.write(EEPROM_MAGIC_ADDR, EEPROM_MAGIC);

		// update centers
		for (uint8_t i = 0; i < n; i++) {
			EEPROM.write(EEPROM_CENTERS_ADDR + i, centers[i]);
		}

		EEPROM.commit();
#else
		// update magic
		EEPROM.update(EEPROM_MAGIC_ADDR, EEPROM_MAGIC);

		// update centers
		for (uint8_t i = 0; i < n; i++) {
			EEPROM.update(EEPROM_CENTERS_ADDR + i, centers[i]);
		}
#endif

		Serial.println("SAVED");
	}
}
