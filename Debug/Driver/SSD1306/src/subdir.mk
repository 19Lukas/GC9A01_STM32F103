################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/SSD1306/src/ssd1306.c 

OBJS += \
./Driver/SSD1306/src/ssd1306.o 

C_DEPS += \
./Driver/SSD1306/src/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/SSD1306/src/%.o Driver/SSD1306/src/%.su Driver/SSD1306/src/%.cyclo: ../Driver/SSD1306/src/%.c Driver/SSD1306/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/GC9A01/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Base/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Config/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/SSD1306/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-SSD1306-2f-src

clean-Driver-2f-SSD1306-2f-src:
	-$(RM) ./Driver/SSD1306/src/ssd1306.cyclo ./Driver/SSD1306/src/ssd1306.d ./Driver/SSD1306/src/ssd1306.o ./Driver/SSD1306/src/ssd1306.su

.PHONY: clean-Driver-2f-SSD1306-2f-src

