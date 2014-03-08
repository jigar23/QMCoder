################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Table/Qmtable.cpp 

OBJS += \
./src/Table/Qmtable.o 

CPP_DEPS += \
./src/Table/Qmtable.d 


# Each subdirectory must supply rules for building sources it contributes
src/Table/%.o: ../src/Table/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


