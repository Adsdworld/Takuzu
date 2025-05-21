################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Apcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Bpcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso15693pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso18092pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso7816pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype1pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype2pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype3pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype4pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype5pcd.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_pcd.c 

OBJS += \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Apcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Bpcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso15693pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso18092pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso7816pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype1pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype2pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype3pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype4pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype5pcd.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_pcd.o 

C_DEPS += \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Apcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso14443Bpcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso15693pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso18092pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_iso7816pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype1pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype2pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype3pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype4pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_nfctype5pcd.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_pcd/lib_pcd.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/NFC03A1/lib_nfc/lib_pcd/%.o: ../drivers/bsp/NFC03A1/lib_nfc/lib_pcd/%.c drivers/bsp/NFC03A1/lib_nfc/lib_pcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

