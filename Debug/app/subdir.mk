################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/game.c \
../app/joystick.c \
../app/main.c \
../app/matrix.c \
../app/takuzu.c 

OBJS += \
./app/game.o \
./app/joystick.o \
./app/main.o \
./app/matrix.o \
./app/takuzu.o 

C_DEPS += \
./app/game.d \
./app/joystick.d \
./app/main.d \
./app/matrix.d \
./app/takuzu.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

