################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cliente.c \
../src/diario.c \
../src/primer_parcial.c \
../src/publicacion.c \
../src/utn.c 

OBJS += \
./src/cliente.o \
./src/diario.o \
./src/primer_parcial.o \
./src/publicacion.o \
./src/utn.o 

C_DEPS += \
./src/cliente.d \
./src/diario.d \
./src/primer_parcial.d \
./src/publicacion.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


