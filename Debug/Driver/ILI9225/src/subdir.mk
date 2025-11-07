################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/ILI9225/src/ili9225.c 

OBJS += \
./Driver/ILI9225/src/ili9225.o 

C_DEPS += \
./Driver/ILI9225/src/ili9225.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/ILI9225/src/%.o Driver/ILI9225/src/%.su Driver/ILI9225/src/%.cyclo: ../Driver/ILI9225/src/%.c Driver/ILI9225/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/GC9A01/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Base/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Config/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/SSD1306/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/ILI9225/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/NRF24L01P/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-ILI9225-2f-src

clean-Driver-2f-ILI9225-2f-src:
	-$(RM) ./Driver/ILI9225/src/ili9225.cyclo ./Driver/ILI9225/src/ili9225.d ./Driver/ILI9225/src/ili9225.o ./Driver/ILI9225/src/ili9225.su

.PHONY: clean-Driver-2f-ILI9225-2f-src

