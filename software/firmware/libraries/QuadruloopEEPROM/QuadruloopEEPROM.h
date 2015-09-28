#ifndef QuadruloopEEPROM_H
#define QuadruloopEEPROM_H

#include <Arduino.h>

#define EEPROM_MAGIC_ADDR 0  // address of magic byte
#define EEPROM_MAGIC 88
#define EEPROM_CENTERS_ADDR 1   // start address for servo centers

namespace QuadruloopEEPROM
{
	void loadConfig(uint8_t n, uint8_t centers[]);
	void saveConfig(uint8_t n, uint8_t centers[]);
};

#endif
