//From https://github.com/Exboom/GC9A01/tree/master

#include <GC9A01.h>
#include "stm32f1xx_ll_gpio.h"
#include "main.h"
#include "string.h"


#define ORIENTATION 2   // Set the display orientation 0,1,2,3

// Command codes:
#define COL_ADDR_SET        0x2A
#define ROW_ADDR_SET        0x2B
#define MEM_WR              0x2C
#define COLOR_MODE          0x3A
#define COLOR_MODE__12_BIT  0x03
#define COLOR_MODE__16_BIT  0x05
#define COLOR_MODE__18_BIT  0x06
#define MEM_WR_CONT         0x3C
#define ON                  1
#define OFF                 0
#define RESET_ON            HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
#define RESET_OFF           HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
#define DC_ON               HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
#define DC_OFF              HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
#define CS_ON               HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
#define CS_OFF              HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

extern SPI_HandleTypeDef hspi1;
/////////////////////////////////////////////////////////
static void display_init(void);
static void display_SetFrame(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY);

static display_GC9A01_t gThisGCA01 = {
		.initialized = false,
};

static inline void display_setMOSI(bool set)
{
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_MOSI].port, gThisGCA01.gpio[DISPLAY_PIN_MOSI].pin, set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static inline void display_setSCK(bool set)
{
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_SCK].port, gThisGCA01.gpio[DISPLAY_PIN_SCK].pin, set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static inline void display_setCS(bool set)
{
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_CS].port, gThisGCA01.gpio[DISPLAY_PIN_CS].pin, set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static inline void display_setRST(bool set)
{
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_RST].port, gThisGCA01.gpio[DISPLAY_PIN_RST].pin, set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


static inline void display_setDC(bool set)
{
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_DC].port, gThisGCA01.gpio[DISPLAY_PIN_DC].pin, set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/////////////////////////////////////////////////////////
static void display_transmitDMA(uint8_t *data, size_t len)
{
	HAL_SPI_Transmit_DMA(gThisGCA01.pSPI, data, len);
}

void GC9A01_spi_tx(uint8_t *data, size_t len) {
    HAL_SPI_Transmit(&hspi1, data, len, 100);
}


void GC9A01_write_command(uint8_t cmd) {
	display_setDC(false);
    display_setCS(false);
    HAL_SPI_Transmit(gThisGCA01.pSPI, &cmd, 1, 100);
    display_setCS(true);
}

void GC9A01_write_data(uint8_t *data, size_t len) {
	display_setDC(true);
    display_setCS(false);
    HAL_SPI_Transmit(gThisGCA01.pSPI, data, len, 100);
    display_setCS(true);
}

void GC9A01_write_commandDMA(uint8_t cmd) {
	while(gThisGCA01.pSPI->hdmatx->State != HAL_DMA_STATE_READY || gThisGCA01.pSPI->State != HAL_SPI_STATE_READY);
	display_setDC(false);
    display_transmitDMA(&cmd, 1);
}

void GC9A01_write_dataDMA(uint8_t *data, size_t len) {
	while(gThisGCA01.pSPI->hdmatx->State != HAL_DMA_STATE_READY || gThisGCA01.pSPI->State != HAL_SPI_STATE_READY);
	display_setDC(true);
    display_transmitDMA(data, len);
}

static inline void GC9A01_write_byte(uint8_t val) {
    GC9A01_write_data(&val, sizeof(val));
}

void GC9A01_write(uint8_t *data, size_t len) {
    GC9A01_write_command(MEM_WR);
    GC9A01_write_data(data, len);
}

void GC9A01_write_continue(uint8_t *data, size_t len) {
    GC9A01_write_command(MEM_WR_CONT);
    GC9A01_write_data(data, len);
}

void GC9A01_writeDMA(uint8_t *data, size_t len) {
    GC9A01_write_commandDMA(MEM_WR);
    GC9A01_write_dataDMA(data, len);
}

void GC9A01_write_continueDMA(uint8_t *data, size_t len) {
    GC9A01_write_commandDMA(MEM_WR_CONT);
    GC9A01_write_dataDMA(data, len);
}

void display_GC9A01_transmitDualData(uint8_t* data, uint16_t len)//todo change data to 6 bit format, or rgb at least, drop 2 lsb
{
	display_setCS(OFF);
	const uint8_t pkgLen = 10 - 1;	//10 bit
	uint16_t pkg1 = 1<<pkgLen;
	uint16_t pkg2 = 1<<pkgLen;

	pkg1 |= (((data[0] & 0b11111100) << 1) | (data[1] >> 3));
	pkg2 |= (((data[1] & 0b00000111) << 6) | (data[2] >> 2));
	display_setCS(OFF);
	for(int8_t indx = pkgLen; indx >= 0; indx--)
	{
		display_setSCK(OFF);
		display_setMOSI(pkg1 & (1<<indx) ? ON : OFF);
		display_setDC(pkg2 & (1<<indx) ? ON : OFF);
		display_setSCK(ON);
		display_setMOSI(OFF);
		display_setDC(OFF);
	}
	display_setCS(ON);
}


ErrorStatus display_GC9A01_enableDualData()
{
	if (!gThisGCA01.initialized)
		return ERROR;


	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_RST].port, gThisGCA01.gpio[DISPLAY_PIN_RST].pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_RST].port, gThisGCA01.gpio[DISPLAY_PIN_RST].pin, GPIO_PIN_SET);

	display_init();
	display_SetFrame(0, gThisGCA01.ResolutionX, 0, gThisGCA01.ResolutionY);

	GC9A01_write_command(0xB3);
	GC9A01_write_byte(1);


	GC9A01_write_command(0xE9);
	GC9A01_write_byte(DISPLAY_INTERFACE_DUAL_DATA);
	GC9A01_write_byte(0);
	GC9A01_write_byte(0);

	uint8_t d[3];
	GC9A01_write(d, 3);

	gThisGCA01.interface = DISPLAY_INTERFACE_DUAL_DATA;

	//For dual data, all pins must be on the same GPIO Port
	for (uint8_t pinIndx = 1; pinIndx < DISPLAY_PIN_COUNT; pinIndx++)
	{
		if (gThisGCA01.gpio[pinIndx].port != gThisGCA01.gpio[0].port)
			return ERROR;
	}
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	for (uint8_t pinIndx = 0; pinIndx < DISPLAY_PIN_COUNT; pinIndx++)
	{
		GPIO_InitStruct.Pin |= gThisGCA01.gpio[pinIndx].pin;
	}

	HAL_GPIO_WritePin(gThisGCA01.gpio[0].port, GPIO_InitStruct.Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(gThisGCA01.gpio[DISPLAY_PIN_RST].port, GPIO_InitStruct.Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(gThisGCA01.gpio[0].port, &GPIO_InitStruct);

	return SUCCESS;
}


ErrorStatus display_GC9A01_init(display_GC9A01_init_t* pInit)
{
	gThisGCA01.ResolutionX = pInit->ResolutionX;
	gThisGCA01.ResolutionY = pInit->ResolutionY;
	gThisGCA01.pSPI = pInit->pSPI;
	memcpy(gThisGCA01.gpio, pInit->gpio, sizeof(display_GC9A01_gpio_t) * DISPLAY_PIN_COUNT);
	gThisGCA01.interface = DISPLAY_INTERFACE_4_WIRE_SPI;
	gThisGCA01.initialized = true;
	//display_init();
	//display_SetFrame(0, pInit->ResolutionX, 0, pInit->ResolutionY);

	return SUCCESS;
}

static void display_SetFrame(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY)
{

    uint8_t data[4];

    GC9A01_write_command(COL_ADDR_SET);
    data[0] = (startX >> 8) & 0xFF;
    data[1] = startX & 0xFF;
    data[2] = (endX >> 8) & 0xFF;
    data[3] = endX & 0xFF;
    GC9A01_write_data(data, sizeof(data));

    GC9A01_write_command(ROW_ADDR_SET);
    data[0] = (startY >> 8) & 0xFF;
    data[1] = startY & 0xFF;
    data[2] = (endY >> 8) & 0xFF;
    data[3] = endY & 0xFF;
    GC9A01_write_data(data, sizeof(data));

}

static void display_init(void) {

	display_setCS(true);
    HAL_Delay(5);
    display_setRST(false);
    HAL_Delay(10);
    display_setRST(true);
    HAL_Delay(120);

    /* Initial Sequence */

    //GC9A01_write_command(0xEF);

    //GC9A01_write_command(0xEB);
    //GC9A01_write_byte(0x14);

    //Inter command set
    GC9A01_write_command(0xFE);
    GC9A01_write_command(0xEF);

    //GC9A01_write_command(0xEB);
    //GC9A01_write_byte(0x14);

    /*GC9A01_write_command(0x84);
    GC9A01_write_byte(0x40);

    GC9A01_write_command(0x85);
    GC9A01_write_byte(0xFF);

    GC9A01_write_command(0x86);
    GC9A01_write_byte(0xFF);

    GC9A01_write_command(0x87);
    GC9A01_write_byte(0xFF);

    GC9A01_write_command(0x88);
    GC9A01_write_byte(0x0A);

    GC9A01_write_command(0x89);
    GC9A01_write_byte(0x21);

    GC9A01_write_command(0x8A);
    GC9A01_write_byte(0x00);

    GC9A01_write_command(0x8B);
    GC9A01_write_byte(0x80);

    GC9A01_write_command(0x8C);
    GC9A01_write_byte(0x01);

    GC9A01_write_command(0x8D);
    GC9A01_write_byte(0x01);

    GC9A01_write_command(0x8E);
    GC9A01_write_byte(0xFF);

    GC9A01_write_command(0x8F);
    GC9A01_write_byte(0xFF);*/


    //Display Function Control
    GC9A01_write_command(0xB6);
    GC9A01_write_byte(0x00);		//XXXXXXXX
    GC9A01_write_byte(0b11101);		//240 Lines

    //Memory Access Control
    GC9A01_write_command(0x36);

#if ORIENTATION == 0
    GC9A01_write_byte(0x18);
#elif ORIENTATION == 1
    GC9A01_write_byte(0x28);
#elif ORIENTATION == 2
    GC9A01_write_byte(0x48);
#else
    GC9A01_write_byte(0x88);
#endif

    //COLMOD
    GC9A01_write_command(COLOR_MODE);
    GC9A01_write_byte(COLOR_MODE__18_BIT);

    /*GC9A01_write_command(0x90);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);

    GC9A01_write_command(0xBD);
    GC9A01_write_byte(0x06);

    GC9A01_write_command(0xBC);
    GC9A01_write_byte(0x00);

    GC9A01_write_command(0xFF);
    GC9A01_write_byte(0x60);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x04);*/

    //Power Control 2
    GC9A01_write_command(0xC3);
    GC9A01_write_byte(0x13);
    //Power Control 3
    GC9A01_write_command(0xC4);
    GC9A01_write_byte(0x13);
    //Power Control 4
    GC9A01_write_command(0xC9);
    GC9A01_write_byte(0x22);

    /*GC9A01_write_command(0xBE);
    GC9A01_write_byte(0x11);

    GC9A01_write_command(0xE1);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x0E);

    GC9A01_write_command(0xDF);
    GC9A01_write_byte(0x21);
    GC9A01_write_byte(0x0c);
    GC9A01_write_byte(0x02);*/

    //Gamma 1
    GC9A01_write_command(0xF0);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);

    //Gamma 2
    GC9A01_write_command(0xF1);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);

    //Gamma 3
    GC9A01_write_command(0xF2);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x26);
    GC9A01_write_byte(0x2A);

    //Gamma 4
    GC9A01_write_command(0xF3);
    GC9A01_write_byte(0x43);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x72);
    GC9A01_write_byte(0x36);
    GC9A01_write_byte(0x37);
    GC9A01_write_byte(0x6F);

    /*GC9A01_write_command(0xED);
    GC9A01_write_byte(0x1B);
    GC9A01_write_byte(0x0B);

    GC9A01_write_command(0xAE);
    GC9A01_write_byte(0x77);

    GC9A01_write_command(0xCD);
    GC9A01_write_byte(0x63);

    GC9A01_write_command(0x70);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x04);
    GC9A01_write_byte(0x0E);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x09);
    GC9A01_write_byte(0x07);
    GC9A01_write_byte(0x08);
    GC9A01_write_byte(0x03);*/

    //Frame Rate
    //GC9A01_write_command(0xE8);
    //GC9A01_write_byte(0x34);

    /*GC9A01_write_command(0x62);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0D);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xED);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x0F);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xEF);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);

    GC9A01_write_command(0x63);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x11);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x18);
    GC9A01_write_byte(0x13);
    GC9A01_write_byte(0x71);
    GC9A01_write_byte(0xF3);
    GC9A01_write_byte(0x70);
    GC9A01_write_byte(0x70);

    GC9A01_write_command(0x64);
    GC9A01_write_byte(0x28);
    GC9A01_write_byte(0x29);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0xF1);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x07);*/

    GC9A01_write_command(0x66);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0xCD);
    GC9A01_write_byte(0x67);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x45);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);

    GC9A01_write_command(0x67);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x3C);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x01);
    GC9A01_write_byte(0x54);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x32);
    GC9A01_write_byte(0x98);

    /*GC9A01_write_command(0x74);
    GC9A01_write_byte(0x10);
    GC9A01_write_byte(0x85);
    GC9A01_write_byte(0x80);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x00);
    GC9A01_write_byte(0x4E);
    GC9A01_write_byte(0x00);

    GC9A01_write_command(0x98);
    GC9A01_write_byte(0x3e);
    GC9A01_write_byte(0x07);*/

    //Tearing effect line
    //GC9A01_write_command(0x35);
    //Display Inversion on
    GC9A01_write_command(0x21);

    //Sleep out
    GC9A01_write_command(0x11);
    HAL_Delay(120);
    //Display ON
    GC9A01_write_command(0x29);
    HAL_Delay(20);

}

