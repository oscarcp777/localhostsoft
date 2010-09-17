################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../miTest/libspopc.o 

C_SRCS += \
../miTest/gmail-poptest.c 

OBJS += \
./miTest/gmail-poptest.o 

C_DEPS += \
./miTest/gmail-poptest.d 


# Each subdirectory must supply rules for building sources it contributes
miTest/%.o: ../miTest/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


