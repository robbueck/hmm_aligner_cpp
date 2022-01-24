################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../file_r_w.cpp \
../main.cpp \
../sequenc_pair.cpp \
../viterbi.cpp 

OBJS += \
./file_r_w.o \
./main.o \
./sequenc_pair.o \
./viterbi.o 

CPP_DEPS += \
./file_r_w.d \
./main.d \
./sequenc_pair.d \
./viterbi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


