################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LED.c \
../Core/Src/algorithm.c \
../Core/Src/direction.c \
../Core/Src/flood_fill.c \
../Core/Src/hugger.c \
../Core/Src/main.c \
../Core/Src/motors.c \
../Core/Src/mouse.c \
../Core/Src/servo.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/switch.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/test.c \
../Core/Src/ultrasonic.c \
../Core/Src/wall_sensor.c 

OBJS += \
./Core/Src/LED.o \
./Core/Src/algorithm.o \
./Core/Src/direction.o \
./Core/Src/flood_fill.o \
./Core/Src/hugger.o \
./Core/Src/main.o \
./Core/Src/motors.o \
./Core/Src/mouse.o \
./Core/Src/servo.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/switch.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/test.o \
./Core/Src/ultrasonic.o \
./Core/Src/wall_sensor.o 

C_DEPS += \
./Core/Src/LED.d \
./Core/Src/algorithm.d \
./Core/Src/direction.d \
./Core/Src/flood_fill.d \
./Core/Src/hugger.d \
./Core/Src/main.d \
./Core/Src/motors.d \
./Core/Src/mouse.d \
./Core/Src/servo.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/switch.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/test.d \
./Core/Src/ultrasonic.d \
./Core/Src/wall_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/algorithm.d ./Core/Src/algorithm.o ./Core/Src/direction.d ./Core/Src/direction.o ./Core/Src/flood_fill.d ./Core/Src/flood_fill.o ./Core/Src/hugger.d ./Core/Src/hugger.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/motors.d ./Core/Src/motors.o ./Core/Src/mouse.d ./Core/Src/mouse.o ./Core/Src/servo.d ./Core/Src/servo.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/switch.d ./Core/Src/switch.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/test.d ./Core/Src/test.o ./Core/Src/ultrasonic.d ./Core/Src/ultrasonic.o ./Core/Src/wall_sensor.d ./Core/Src/wall_sensor.o

.PHONY: clean-Core-2f-Src

