################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/epaper/stm32g4_epaper_com.c \
../drivers/bsp/epaper/stm32g4_epaper_demo.c \
../drivers/bsp/epaper/stm32g4_epaper_if.c \
../drivers/bsp/epaper/stm32g4_epaper_imagedata.c \
../drivers/bsp/epaper/stm32g4_epaper_paint.c 

OBJS += \
./drivers/bsp/epaper/stm32g4_epaper_com.o \
./drivers/bsp/epaper/stm32g4_epaper_demo.o \
./drivers/bsp/epaper/stm32g4_epaper_if.o \
./drivers/bsp/epaper/stm32g4_epaper_imagedata.o \
./drivers/bsp/epaper/stm32g4_epaper_paint.o 

C_DEPS += \
./drivers/bsp/epaper/stm32g4_epaper_com.d \
./drivers/bsp/epaper/stm32g4_epaper_demo.d \
./drivers/bsp/epaper/stm32g4_epaper_if.d \
./drivers/bsp/epaper/stm32g4_epaper_imagedata.d \
./drivers/bsp/epaper/stm32g4_epaper_paint.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/epaper/%.o: ../drivers/bsp/epaper/%.c drivers/bsp/epaper/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

