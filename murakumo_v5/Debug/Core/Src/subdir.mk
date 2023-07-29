################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/IMU.c \
../Core/Src/LED.c \
../Core/Src/Rotary.c \
../Core/Src/Switch.c \
../Core/Src/analog.c \
../Core/Src/correction.c \
../Core/Src/course.c \
../Core/Src/defines.c \
../Core/Src/encoder.c \
../Core/Src/fixed_section.c \
../Core/Src/flash.c \
../Core/Src/function.c \
../Core/Src/geometry.c \
../Core/Src/length.c \
../Core/Src/main.c \
../Core/Src/motor.c \
../Core/Src/pid.c \
../Core/Src/print.c \
../Core/Src/revision.c \
../Core/Src/section_length.c \
../Core/Src/sidesensor.c \
../Core/Src/slow.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim10.c \
../Core/Src/tim11.c \
../Core/Src/tim6.c \
../Core/Src/tim7.c \
../Core/Src/time.c \
../Core/Src/tracer.c \
../Core/Src/velodef.c \
../Core/Src/velotrace.c \
../Core/Src/virtual_marker.c 

OBJS += \
./Core/Src/IMU.o \
./Core/Src/LED.o \
./Core/Src/Rotary.o \
./Core/Src/Switch.o \
./Core/Src/analog.o \
./Core/Src/correction.o \
./Core/Src/course.o \
./Core/Src/defines.o \
./Core/Src/encoder.o \
./Core/Src/fixed_section.o \
./Core/Src/flash.o \
./Core/Src/function.o \
./Core/Src/geometry.o \
./Core/Src/length.o \
./Core/Src/main.o \
./Core/Src/motor.o \
./Core/Src/pid.o \
./Core/Src/print.o \
./Core/Src/revision.o \
./Core/Src/section_length.o \
./Core/Src/sidesensor.o \
./Core/Src/slow.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim10.o \
./Core/Src/tim11.o \
./Core/Src/tim6.o \
./Core/Src/tim7.o \
./Core/Src/time.o \
./Core/Src/tracer.o \
./Core/Src/velodef.o \
./Core/Src/velotrace.o \
./Core/Src/virtual_marker.o 

C_DEPS += \
./Core/Src/IMU.d \
./Core/Src/LED.d \
./Core/Src/Rotary.d \
./Core/Src/Switch.d \
./Core/Src/analog.d \
./Core/Src/correction.d \
./Core/Src/course.d \
./Core/Src/defines.d \
./Core/Src/encoder.d \
./Core/Src/fixed_section.d \
./Core/Src/flash.d \
./Core/Src/function.d \
./Core/Src/geometry.d \
./Core/Src/length.d \
./Core/Src/main.d \
./Core/Src/motor.d \
./Core/Src/pid.d \
./Core/Src/print.d \
./Core/Src/revision.d \
./Core/Src/section_length.d \
./Core/Src/sidesensor.d \
./Core/Src/slow.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim10.d \
./Core/Src/tim11.d \
./Core/Src/tim6.d \
./Core/Src/tim7.d \
./Core/Src/time.d \
./Core/Src/tracer.d \
./Core/Src/velodef.d \
./Core/Src/velotrace.d \
./Core/Src/virtual_marker.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F405xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" -u_printf_float -lm

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/IMU.cyclo ./Core/Src/IMU.d ./Core/Src/IMU.o ./Core/Src/IMU.su ./Core/Src/LED.cyclo ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/LED.su ./Core/Src/Rotary.cyclo ./Core/Src/Rotary.d ./Core/Src/Rotary.o ./Core/Src/Rotary.su ./Core/Src/Switch.cyclo ./Core/Src/Switch.d ./Core/Src/Switch.o ./Core/Src/Switch.su ./Core/Src/analog.cyclo ./Core/Src/analog.d ./Core/Src/analog.o ./Core/Src/analog.su ./Core/Src/correction.cyclo ./Core/Src/correction.d ./Core/Src/correction.o ./Core/Src/correction.su ./Core/Src/course.cyclo ./Core/Src/course.d ./Core/Src/course.o ./Core/Src/course.su ./Core/Src/defines.cyclo ./Core/Src/defines.d ./Core/Src/defines.o ./Core/Src/defines.su ./Core/Src/encoder.cyclo ./Core/Src/encoder.d ./Core/Src/encoder.o ./Core/Src/encoder.su ./Core/Src/fixed_section.cyclo ./Core/Src/fixed_section.d ./Core/Src/fixed_section.o ./Core/Src/fixed_section.su ./Core/Src/flash.cyclo ./Core/Src/flash.d ./Core/Src/flash.o ./Core/Src/flash.su ./Core/Src/function.cyclo ./Core/Src/function.d ./Core/Src/function.o ./Core/Src/function.su ./Core/Src/geometry.cyclo ./Core/Src/geometry.d ./Core/Src/geometry.o ./Core/Src/geometry.su ./Core/Src/length.cyclo ./Core/Src/length.d ./Core/Src/length.o ./Core/Src/length.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor.cyclo ./Core/Src/motor.d ./Core/Src/motor.o ./Core/Src/motor.su ./Core/Src/pid.cyclo ./Core/Src/pid.d ./Core/Src/pid.o ./Core/Src/pid.su ./Core/Src/print.cyclo ./Core/Src/print.d ./Core/Src/print.o ./Core/Src/print.su ./Core/Src/revision.cyclo ./Core/Src/revision.d ./Core/Src/revision.o ./Core/Src/revision.su ./Core/Src/section_length.cyclo ./Core/Src/section_length.d ./Core/Src/section_length.o ./Core/Src/section_length.su ./Core/Src/sidesensor.cyclo ./Core/Src/sidesensor.d ./Core/Src/sidesensor.o ./Core/Src/sidesensor.su ./Core/Src/slow.cyclo ./Core/Src/slow.d ./Core/Src/slow.o ./Core/Src/slow.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim10.cyclo ./Core/Src/tim10.d ./Core/Src/tim10.o ./Core/Src/tim10.su ./Core/Src/tim11.cyclo ./Core/Src/tim11.d ./Core/Src/tim11.o ./Core/Src/tim11.su ./Core/Src/tim6.cyclo ./Core/Src/tim6.d ./Core/Src/tim6.o ./Core/Src/tim6.su ./Core/Src/tim7.cyclo ./Core/Src/tim7.d ./Core/Src/tim7.o ./Core/Src/tim7.su ./Core/Src/time.cyclo ./Core/Src/time.d ./Core/Src/time.o ./Core/Src/time.su ./Core/Src/tracer.cyclo ./Core/Src/tracer.d ./Core/Src/tracer.o ./Core/Src/tracer.su ./Core/Src/velodef.cyclo ./Core/Src/velodef.d ./Core/Src/velodef.o ./Core/Src/velodef.su ./Core/Src/velotrace.cyclo ./Core/Src/velotrace.d ./Core/Src/velotrace.o ./Core/Src/velotrace.su ./Core/Src/virtual_marker.cyclo ./Core/Src/virtual_marker.d ./Core/Src/virtual_marker.o ./Core/Src/virtual_marker.su

.PHONY: clean-Core-2f-Src

