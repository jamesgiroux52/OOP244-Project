################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ms4.cpp \
../src/ms4_Allocator.cpp \
../src/ms4_MyGood.cpp 

OBJS += \
./src/ms4.o \
./src/ms4_Allocator.o \
./src/ms4_MyGood.o 

CPP_DEPS += \
./src/ms4.d \
./src/ms4_Allocator.d \
./src/ms4_MyGood.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


