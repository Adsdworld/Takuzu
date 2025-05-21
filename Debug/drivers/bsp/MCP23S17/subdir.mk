################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/MCP23S17/stm32g4_mcp23s17.c 

OBJS += \
./drivers/bsp/MCP23S17/stm32g4_mcp23s17.o 

C_DEPS += \
./drivers/bsp/MCP23S17/stm32g4_mcp23s17.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/MCP23S17/%.o: ../drivers/bsp/MCP23S17/%.c drivers/bsp/MCP23S17/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

