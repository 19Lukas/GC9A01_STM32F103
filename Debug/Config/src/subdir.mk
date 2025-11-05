################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Config/src/hardware_config.c 

OBJS += \
./Config/src/hardware_config.o 

C_DEPS += \
./Config/src/hardware_config.d 


# Each subdirectory must supply rules for building sources it contributes
Config/src/%.o Config/src/%.su Config/src/%.cyclo: ../Config/src/%.c Config/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Driver/GC9A01/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Base/inc" -I"D:/OneDrive/Projekte/RoundLCD/Git/GC9A01_STM32F103/Config/inc" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Config-2f-src

clean-Config-2f-src:
	-$(RM) ./Config/src/hardware_config.cyclo ./Config/src/hardware_config.d ./Config/src/hardware_config.o ./Config/src/hardware_config.su

.PHONY: clean-Config-2f-src

