################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/examples/winpoptest2.o 

C_SRCS += \
../lib/examples/butcher.c \
../lib/examples/poptest1.c \
../lib/examples/poptest2.c \
../lib/examples/poptest3.c \
../lib/examples/winpoptest1.c \
../lib/examples/winpoptest2.c 

OBJS += \
./lib/examples/butcher.o \
./lib/examples/poptest1.o \
./lib/examples/poptest2.o \
./lib/examples/poptest3.o \
./lib/examples/winpoptest1.o \
./lib/examples/winpoptest2.o 

C_DEPS += \
./lib/examples/butcher.d \
./lib/examples/poptest1.d \
./lib/examples/poptest2.d \
./lib/examples/poptest3.d \
./lib/examples/winpoptest1.d \
./lib/examples/winpoptest2.d 


# Each subdirectory must supply rules for building sources it contributes
lib/examples/%.o: ../lib/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


