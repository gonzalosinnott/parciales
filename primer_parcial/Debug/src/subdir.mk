################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/client.c \
../src/info.c \
../src/main.c \
../src/publication.c \
../src/utn.c 

OBJS += \
./src/client.o \
./src/info.o \
./src/main.o \
./src/publication.o \
./src/utn.o 

C_DEPS += \
./src/client.d \
./src/info.d \
./src/main.d \
./src/publication.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


