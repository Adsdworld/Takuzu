################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/NFC03A1/lib_nfc/common/lib_95HFConfigManager.c 

OBJS += \
./drivers/bsp/NFC03A1/lib_nfc/common/lib_95HFConfigManager.o 

C_DEPS += \
./drivers/bsp/NFC03A1/lib_nfc/common/lib_95HFConfigManager.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/NFC03A1/lib_nfc/common/%.o: ../drivers/bsp/NFC03A1/lib_nfc/common/%.c drivers/bsp/NFC03A1/lib_nfc/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

