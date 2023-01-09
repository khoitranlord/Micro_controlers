################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f103c6tx.s 

C_SRCS += \
../Core/Startup/stm32f1xx_it.c 

OBJS += \
./Core/Startup/startup_stm32f103c6tx.o \
./Core/Startup/stm32f1xx_it.o 

S_DEPS += \
./Core/Startup/startup_stm32f103c6tx.d 

C_DEPS += \
./Core/Startup/stm32f1xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
Core/Startup/%.o Core/Startup/%.su: ../Core/Startup/%.c Core/Startup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f103c6tx.d ./Core/Startup/startup_stm32f103c6tx.o ./Core/Startup/stm32f1xx_it.d ./Core/Startup/stm32f1xx_it.o ./Core/Startup/stm32f1xx_it.su

.PHONY: clean-Core-2f-Startup

