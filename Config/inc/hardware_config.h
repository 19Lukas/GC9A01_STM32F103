#include "GC9A01.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
display_GC9A01_init_t gDisplayGCA01Init = {
		.ResolutionX = 240,
		.ResolutionY = 240,
		.pSPI = &hspi1,
		.gpio = {
				.portCS = GPIOA,
				.pinCS = 3,
				.portDC = GPIOA,
				.pinDC = 6,
				.portRST = GPIOA,
				.pinRST = 4,
				.portSCK = GPIOA,
				.pinSCK = 5,
				.portMOSI = GPIOA,
				.pinMOSI = 7,
		},
};
