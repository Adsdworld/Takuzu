################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_95HF_wrapper.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_AAR.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Email.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Geo.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_MyApp.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_SMS.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Text.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_URI.c \
../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Vcard.c 

OBJS += \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_95HF_wrapper.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_AAR.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Email.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Geo.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_MyApp.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_SMS.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Text.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_URI.o \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Vcard.o 

C_DEPS += \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_95HF_wrapper.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_AAR.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Email.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Geo.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_MyApp.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_SMS.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Text.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_URI.d \
./drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/lib_NDEF_Vcard.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/%.o: ../drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/%.c drivers/bsp/NFC03A1/lib_nfc/lib_NDEF/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../core/Inc -I../drivers/stm32g4xx_hal/Inc -I../drivers/stm32g4xx_hal/Inc/Legacy -I../drivers/cmsis/Device/ST/STM32G4xx/Include -I../drivers/cmsis/Include -I../app -I../drivers/bsp -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

