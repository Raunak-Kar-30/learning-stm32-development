################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/exti_interrupts.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/systick_interrupt.c \
../Src/timer_interrupt.c \
../Src/usart_interrupt.c \
../Src/utils.c 

OBJS += \
./Src/exti_interrupts.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/systick_interrupt.o \
./Src/timer_interrupt.o \
./Src/usart_interrupt.o \
./Src/utils.o 

C_DEPS += \
./Src/exti_interrupts.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/systick_interrupt.d \
./Src/timer_interrupt.d \
./Src/usart_interrupt.d \
./Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I/home/raunak-kar/Dev_tools/STM32/CMSIS/F446RE/Device/ST/STM32F4xx/Include -I/home/raunak-kar/Dev_tools/STM32/CMSIS/F446RE/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/exti_interrupts.cyclo ./Src/exti_interrupts.d ./Src/exti_interrupts.o ./Src/exti_interrupts.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/systick_interrupt.cyclo ./Src/systick_interrupt.d ./Src/systick_interrupt.o ./Src/systick_interrupt.su ./Src/timer_interrupt.cyclo ./Src/timer_interrupt.d ./Src/timer_interrupt.o ./Src/timer_interrupt.su ./Src/usart_interrupt.cyclo ./Src/usart_interrupt.d ./Src/usart_interrupt.o ./Src/usart_interrupt.su ./Src/utils.cyclo ./Src/utils.d ./Src/utils.o ./Src/utils.su

.PHONY: clean-Src

