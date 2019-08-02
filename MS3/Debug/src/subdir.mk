################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Error.cpp \
../src/Good.cpp \
../src/ms3.cpp \
../src/ms3_MyGood.cpp 

OBJS += \
./src/Error.o \
./src/Good.o \
./src/ms3.o \
./src/ms3_MyGood.o 

CPP_DEPS += \
./src/Error.d \
./src/Good.d \
./src/ms3.d \
./src/ms3_MyGood.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


