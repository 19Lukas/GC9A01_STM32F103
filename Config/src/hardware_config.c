#include "hardware_config.h"

extern SPI_HandleTypeDef hspi1;
display_GC9A01_init_t gDisplayGCA01Init = {
		.ResolutionX = 240,
		.ResolutionY = 240,
		.pSPI = &hspi1,
		.gpio[DISPLAY_PIN_CS].port = DISPLAY_CS_GPIO_Port,
		.gpio[DISPLAY_PIN_CS].pin = DISPLAY_CS_Pin,
		.gpio[DISPLAY_PIN_DC].port = DISPLAY_DC_GPIO_Port,
		.gpio[DISPLAY_PIN_DC].pin = DISPLAY_DC_Pin,
		.gpio[DISPLAY_PIN_RST].port = DISPLAY_RST_GPIO_Port,
		.gpio[DISPLAY_PIN_RST].pin = DISPLAY_RST_Pin,
		.gpio[DISPLAY_PIN_MOSI].port = DISPLAY_MOSI_GPIO_Port,
		.gpio[DISPLAY_PIN_MOSI].pin = DISPLAY_MOSI_Pin,
		.gpio[DISPLAY_PIN_SCK].port = DISPLAY_SCK_GPIO_Port,
		.gpio[DISPLAY_PIN_SCK].pin = DISPLAY_SCK_Pin,
};
