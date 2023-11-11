################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/data_smoothing/sample.c \
../Core/Src/data_smoothing/smoothing.c \
../Core/Src/data_smoothing/smoothing_64.c 

OBJS += \
./Core/Src/data_smoothing/sample.o \
./Core/Src/data_smoothing/smoothing.o \
./Core/Src/data_smoothing/smoothing_64.o 

C_DEPS += \
./Core/Src/data_smoothing/sample.d \
./Core/Src/data_smoothing/smoothing.d \
./Core/Src/data_smoothing/smoothing_64.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/data_smoothing/%.o Core/Src/data_smoothing/%.su Core/Src/data_smoothing/%.cyclo: ../Core/Src/data_smoothing/%.c Core/Src/data_smoothing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-data_smoothing

clean-Core-2f-Src-2f-data_smoothing:
	-$(RM) ./Core/Src/data_smoothing/sample.cyclo ./Core/Src/data_smoothing/sample.d ./Core/Src/data_smoothing/sample.o ./Core/Src/data_smoothing/sample.su ./Core/Src/data_smoothing/smoothing.cyclo ./Core/Src/data_smoothing/smoothing.d ./Core/Src/data_smoothing/smoothing.o ./Core/Src/data_smoothing/smoothing.su ./Core/Src/data_smoothing/smoothing_64.cyclo ./Core/Src/data_smoothing/smoothing_64.d ./Core/Src/data_smoothing/smoothing_64.o ./Core/Src/data_smoothing/smoothing_64.su

.PHONY: clean-Core-2f-Src-2f-data_smoothing

