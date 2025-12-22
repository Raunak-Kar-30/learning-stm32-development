################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc_conversion.c \
../Src/dac_signal_gen.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer.c \
../Src/usart.c 

OBJS += \
./Src/adc_conversion.o \
./Src/dac_signal_gen.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer.o \
./Src/usart.o 

C_DEPS += \
./Src/adc_conversion.d \
./Src/dac_signal_gen.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I/home/raunak-kar/Dev_tools/STM32/CMSIS/F446RE/Device/ST/STM32F4xx/Include -I/home/raunak-kar/Dev_tools/STM32/CMSIS/F446RE/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc_conversion.cyclo ./Src/adc_conversion.d ./Src/adc_conversion.o ./Src/adc_conversion.su ./Src/dac_signal_gen.cyclo ./Src/dac_signal_gen.d ./Src/dac_signal_gen.o ./Src/dac_signal_gen.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su ./Src/usart.cyclo ./Src/usart.d ./Src/usart.o ./Src/usart.su

.PHONY: clean-Src

