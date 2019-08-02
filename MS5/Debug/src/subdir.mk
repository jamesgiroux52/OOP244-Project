################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Date.cpp \
../src/Error.cpp \
../src/Good.cpp \
../src/Perishable.cpp \
../src/ms5.cpp 

OBJS += \
./src/Date.o \
./src/Error.o \
./src/Good.o \
./src/Perishable.o \
./src/ms5.o 

CPP_DEPS += \
./src/Date.d \
./src/Error.d \
./src/Good.d \
./src/Perishable.d \
./src/ms5.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


