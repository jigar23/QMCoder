################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/QMTable/QMtable.cpp 

OBJS += \
./src/QMTable/QMtable.o 

CPP_DEPS += \
./src/QMTable/QMtable.d 


# Each subdirectory must supply rules for building sources it contributes
src/QMTable/%.o: ../src/QMTable/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


