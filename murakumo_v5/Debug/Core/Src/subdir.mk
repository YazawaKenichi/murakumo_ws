################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/IMU.c \
../Core/Src/LED.c \
../Core/Src/Rotary.c \
../Core/Src/Switch.c \
../Core/Src/analog.c \
../Core/Src/course.c \
../Core/Src/defines.c \
../Core/Src/encoder.c \
../Core/Src/flash.c \
../Core/Src/function.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/pid.c \
../Core/Src/print.c \
../Core/Src/sidesensor.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim10.c \
../Core/Src/tim11.c \
../Core/Src/tim6.c \
../Core/Src/tracer.c \
../Core/Src/velodef.c \
../Core/Src/velotrace.c 

OBJS += \
./Core/Src/IMU.o \
./Core/Src/LED.o \
./Core/Src/Rotary.o \
./Core/Src/Switch.o \
./Core/Src/analog.o \
./Core/Src/course.o \
./Core/Src/defines.o \
./Core/Src/encoder.o \
./Core/Src/flash.o \
./Core/Src/function.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/pid.o \
./Core/Src/print.o \
./Core/Src/sidesensor.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim10.o \
./Core/Src/tim11.o \
./Core/Src/tim6.o \
./Core/Src/tracer.o \
./Core/Src/velodef.o \
./Core/Src/velotrace.o 

C_DEPS += \
./Core/Src/IMU.d \
./Core/Src/LED.d \
./Core/Src/Rotary.d \
./Core/Src/Switch.d \
./Core/Src/analog.d \
./Core/Src/course.d \
./Core/Src/defines.d \
./Core/Src/encoder.d \
./Core/Src/flash.d \
./Core/Src/function.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/pid.d \
./Core/Src/print.d \
./Core/Src/sidesensor.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim10.d \
./Core/Src/tim11.d \
./Core/Src/tim6.d \
./Core/Src/tracer.d \
./Core/Src/velodef.d \
./Core/Src/velotrace.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" -u_printf_float -lm --debug
Core/Src/tracer.o: ../Core/Src/tracer.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/IMU.d ./Core/Src/IMU.o ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/Rotary.d ./Core/Src/Rotary.o ./Core/Src/Switch.d ./Core/Src/Switch.o ./Core/Src/analog.d ./Core/Src/analog.o ./Core/Src/course.d ./Core/Src/course.o ./Core/Src/defines.d ./Core/Src/defines.o ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/flash.d ./Core/Src/flash.o ./Core/Src/function.d ./Core/Src/function.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/pid.d ./Core/Src/pid.o ./Core/Src/print.d ./Core/Src/print.o ./Core/Src/sidesensor.d ./Core/Src/sidesensor.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/tim10.d ./Core/Src/tim10.o ./Core/Src/tim11.d ./Core/Src/tim11.o ./Core/Src/tim6.d ./Core/Src/tim6.o ./Core/Src/tracer.d ./Core/Src/tracer.o ./Core/Src/velodef.d ./Core/Src/velodef.o ./Core/Src/velotrace.d ./Core/Src/velotrace.o

.PHONY: clean-Core-2f-Src

