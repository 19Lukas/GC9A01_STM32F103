//From https://github.com/Exboom/GC9A01/tree/master

#pragma once
#include "main.h"
#include "stdbool.h"

typedef struct
{
	GPIO_TypeDef* portCS;
	GPIO_TypeDef* portDC;
	GPIO_TypeDef* portRST;
	GPIO_TypeDef* portSCK;
	GPIO_TypeDef* portMOSI;
	uint8_t pinCS;
	uint8_t pinDC;
	uint8_t pinRST;
	uint8_t pinMOSI;
	uint8_t pinSCK;
}display_GC9A01_gpio_init_t;

typedef struct
{
	uint16_t ResolutionX;
	uint16_t ResolutionY;
	SPI_HandleTypeDef* pSPI;
	display_GC9A01_gpio_init_t gpio;
}display_GC9A01_init_t;

typedef struct
{
	uint16_t ResolutionX;
	uint16_t ResolutionY;
	SPI_HandleTypeDef* pSPI;
	display_GC9A01_gpio_init_t gpio;
	bool initialized;
}display_GC9A01_t;

ErrorStatus display_GC9A01_init(display_GC9A01_init_t* pInit);


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

struct GC9A01_point {
    uint16_t X, Y;
};

struct GC9A01_frame {
    struct GC9A01_point start, end;
};

void GC9A01_init(void);
void GC9A01_set_frame(struct GC9A01_frame frame);
void GC9A01_write(uint8_t *data, size_t len);
void GC9A01_write_continue(uint8_t *data, size_t len);

void GC9A01_write_data(uint8_t *data, size_t len);
void GC9A01_write_command(uint8_t cmd);


#ifdef __cplusplus
}
#endif

