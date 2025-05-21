################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/VL53L0X/stm32g4_vl53l0x_demo.c \
../drivers/bsp/VL53L0X/vl53l0x_api.c \
../drivers/bsp/VL53L0X/vl53l0x_api_calibration.c \
../drivers/bsp/VL53L0X/vl53l0x_api_core.c \
../drivers/bsp/VL53L0X/vl53l0x_api_ranging.c \
../drivers/bsp/VL53L0X/vl53l0x_api_strings.c \
../drivers/bsp/VL53L0X/vl53l0x_platform.c \
../drivers/bsp/VL53L0X/vl53l0x_platform_log.c 

OBJS += \
./drivers/bsp/VL53L0X/stm32g4_vl53l0x_demo.o \
./drivers/bsp/VL53L0X/vl53l0x_api.o \
./drivers/bsp/VL53L0X/vl53l0x_api_calibration.o \
./drivers/bsp/VL53L0X/vl53l0x_api_core.o \
./drivers/bsp/VL53L0X/vl53l0x_api_ranging.o \
./drivers/bsp/VL53L0X/vl53l0x_api_strings.o \
./drivers/bsp/VL53L0X/vl53l0x_platform.o \
./drivers/bsp/VL53L0X/vl53l0x_platform_log.o 

C_DEPS += \
./drivers/bsp/VL53L0X/stm32g4_vl53l0x_demo.d \
./drivers/bsp/VL53L0X/vl53l0x_api.d \
./drivers/bsp/VL53L0X/vl53l0x_api_calibration.d \
./drivers/bsp/VL53L0X/vl53l0x_api_core.d \
./drivers/bsp/VL53L0X/vl53l0x_api_ranging.d \
./drivers/bsp/VL53L0X/vl53l0x_api_strings.d \
./drivers/bsp/VL53L0X/vl53l0x_platform.d \
./drivers/bsp/VL53L0X/vl53l0x_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/VL53L0X/%.o: ../drivers/bsp/VL53L0X/%.c drivers/bsp/VL53L0X/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

