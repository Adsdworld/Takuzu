################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/stm32g4_adc.c \
../drivers/bsp/stm32g4_dac.c \
../drivers/bsp/stm32g4_extit.c \
../drivers/bsp/stm32g4_flash.c \
../drivers/bsp/stm32g4_gpio.c \
../drivers/bsp/stm32g4_i2c.c \
../drivers/bsp/stm32g4_rtc.c \
../drivers/bsp/stm32g4_spi.c \
../drivers/bsp/stm32g4_sys.c \
../drivers/bsp/stm32g4_systick.c \
../drivers/bsp/stm32g4_timer.c \
../drivers/bsp/stm32g4_uart.c 

OBJS += \
./drivers/bsp/stm32g4_adc.o \
./drivers/bsp/stm32g4_dac.o \
./drivers/bsp/stm32g4_extit.o \
./drivers/bsp/stm32g4_flash.o \
./drivers/bsp/stm32g4_gpio.o \
./drivers/bsp/stm32g4_i2c.o \
./drivers/bsp/stm32g4_rtc.o \
./drivers/bsp/stm32g4_spi.o \
./drivers/bsp/stm32g4_sys.o \
./drivers/bsp/stm32g4_systick.o \
./drivers/bsp/stm32g4_timer.o \
./drivers/bsp/stm32g4_uart.o 

C_DEPS += \
./drivers/bsp/stm32g4_adc.d \
./drivers/bsp/stm32g4_dac.d \
./drivers/bsp/stm32g4_extit.d \
./drivers/bsp/stm32g4_flash.d \
./drivers/bsp/stm32g4_gpio.d \
./drivers/bsp/stm32g4_i2c.d \
./drivers/bsp/stm32g4_rtc.d \
./drivers/bsp/stm32g4_spi.d \
./drivers/bsp/stm32g4_sys.d \
./drivers/bsp/stm32g4_systick.d \
./drivers/bsp/stm32g4_timer.d \
./drivers/bsp/stm32g4_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/%.o: ../drivers/bsp/%.c drivers/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

