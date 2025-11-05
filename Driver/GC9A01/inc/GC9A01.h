//From https://github.com/Exboom/GC9A01/tree/master

#pragma once
#include "main.h"
#include "stdbool.h"
#include "stdint.h"

typedef enum
{
	DISPLAY_INTERFACE_4_WIRE_SPI = 0,
	DISPLAY_INTERFACE_DUAL_DATA = 0b1001, 	//262k, 1 pixel
}disaply_GC9A01_interface_e;

typedef enum
{
	DISPLAY_PIN_CS,
	DISPLAY_PIN_DC,
	DISPLAY_PIN_RST,
	DISPLAY_PIN_MOSI,
	DISPLAY_PIN_SCK,
	DISPLAY_PIN_COUNT,
}display_GC9A01_gpioName_e;

typedef struct
{
	GPIO_TypeDef* port;
	uint32_t pin;
}display_GC9A01_gpio_t;

typedef struct
{
	uint16_t ResolutionX;
	uint16_t ResolutionY;
	SPI_HandleTypeDef* pSPI;
	display_GC9A01_gpio_t gpio[DISPLAY_PIN_COUNT];
}display_GC9A01_init_t;

typedef struct
{
	uint16_t ResolutionX;
	uint16_t ResolutionY;
	SPI_HandleTypeDef* pSPI;
	display_GC9A01_gpio_t gpio[DISPLAY_PIN_COUNT];
	disaply_GC9A01_interface_e interface;
	bool initialized;
}display_GC9A01_t;

ErrorStatus display_GC9A01_init(display_GC9A01_init_t* pInit);
ErrorStatus display_GC9A01_enableDualData();
void display_GC9A01_transmitDualData(uint8_t* data, uint16_t len);

/////////////////////////////////////////////
#include <stdint.h>
#include <stddef.h>
#include "stm32f1xx_ll_utils.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

// Hardware abstraction layer
// Should be defined by the user of the library
void GC9A01_set_reset(uint8_t val);
void GC9A01_set_data_command(uint8_t val);


void GC9A01_write(uint8_t *data, size_t len);
void GC9A01_write_continue(uint8_t *data, size_t len);

void GC9A01_write_data(uint8_t *data, size_t len);
void GC9A01_write_command(uint8_t cmd);
void GC9A01_write_dataDMA(uint8_t *data, size_t len);
void GC9A01_writeDMA(uint8_t *data, size_t len);
void GC9A01_write_continueDMA(uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

