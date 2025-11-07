################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/NRF24L01P/src/nrf24l01p.c 

OBJS += \
./Driver/NRF24L01P/src/nrf24l01p.o 

C_DEPS += \
./Driver/NRF24L01P/src/nrf24l01p.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/NRF24L01P/src/%.o Driver/NRF24L01P/src/%.su Driver/NRF24L01P/src/%.cyclo: ../Driver/NRF24L01P/src/%.c Driver/NRF24L01P/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/GC9A01/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Base/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Config/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/SSD1306/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/ILI9225/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/NRF24L01P/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-NRF24L01P-2f-src

clean-Driver-2f-NRF24L01P-2f-src:
	-$(RM) ./Driver/NRF24L01P/src/nrf24l01p.cyclo ./Driver/NRF24L01P/src/nrf24l01p.d ./Driver/NRF24L01P/src/nrf24l01p.o ./Driver/NRF24L01P/src/nrf24l01p.su

.PHONY: clean-Driver-2f-NRF24L01P-2f-src

