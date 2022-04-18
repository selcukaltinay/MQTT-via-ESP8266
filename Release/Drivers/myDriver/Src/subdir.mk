################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/myDriver/Src/mqtt.c 

OBJS += \
./Drivers/myDriver/Src/mqtt.o 

C_DEPS += \
./Drivers/myDriver/Src/mqtt.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/myDriver/Src/%.o: ../Drivers/myDriver/Src/%.c Drivers/myDriver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-myDriver-2f-Src

clean-Drivers-2f-myDriver-2f-Src:
	-$(RM) ./Drivers/myDriver/Src/mqtt.d ./Drivers/myDriver/Src/mqtt.o

.PHONY: clean-Drivers-2f-myDriver-2f-Src

