################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/data_smoothing/smoothing.c 

OBJS += \
./Core/Inc/data_smoothing/smoothing.o 

C_DEPS += \
./Core/Inc/data_smoothing/smoothing.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/data_smoothing/%.o Core/Inc/data_smoothing/%.su Core/Inc/data_smoothing/%.cyclo: ../Core/Inc/data_smoothing/%.c Core/Inc/data_smoothing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-data_smoothing

clean-Core-2f-Inc-2f-data_smoothing:
	-$(RM) ./Core/Inc/data_smoothing/smoothing.cyclo ./Core/Inc/data_smoothing/smoothing.d ./Core/Inc/data_smoothing/smoothing.o ./Core/Inc/data_smoothing/smoothing.su

.PHONY: clean-Core-2f-Inc-2f-data_smoothing

