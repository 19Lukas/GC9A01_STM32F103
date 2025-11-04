#include "GC9A01.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
display_GC9A01_init_t gDisplayGCA01Init = {
		.ResolutionX = 240,
		.ResolutionY = 240,
		.pSPI = &hspi1,
		.gpio = {
				.portCS = DISPLAY_CS_GPIO_Port,
				.pinCS = DISPLAY_CS_Pin,
				.portDC = DISPLAY_DC_GPIO_Port,
				.pinDC = DISPLAY_DC_Pin,
				.portRST = DISPLAY_RST_GPIO_Port,
				.pinRST = DISPLAY_RST_Pin,
				.portSCK = DISPLAY_SCK_GPIO_Port,
				.pinSCK = DISPLAY_SCK_Pin,
				.portMOSI = DISPLAY_MOSI_GPIO_Port,
				.pinMOSI = DISPLAY_MOSI_Pin,
		},
};
