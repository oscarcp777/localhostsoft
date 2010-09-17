################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/format.o \
../lib/libspopc.o \
../lib/mutex.o \
../lib/objects.o \
../lib/parsing.o \
../lib/queries.o \
../lib/session.o 

C_SRCS += \
../lib/format.c \
../lib/libspopc.c \
../lib/mutex.c \
../lib/objects.c \
../lib/parsing.c \
../lib/queries.c \
../lib/session.c 

OBJS += \
./lib/format.o \
./lib/libspopc.o \
./lib/mutex.o \
./lib/objects.o \
./lib/parsing.o \
./lib/queries.o \
./lib/session.o 

C_DEPS += \
./lib/format.d \
./lib/libspopc.d \
./lib/mutex.d \
./lib/objects.d \
./lib/parsing.d \
./lib/queries.d \
./lib/session.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


