################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Solvers/SubGradientDescent/ISTA/ista.cpp \
../Solvers/SubGradientDescent/ISTA/viennacl_ista.cpp 

OBJS += \
./Solvers/SubGradientDescent/ISTA/ista.o \
./Solvers/SubGradientDescent/ISTA/viennacl_ista.o 

CPP_DEPS += \
./Solvers/SubGradientDescent/ISTA/ista.d \
./Solvers/SubGradientDescent/ISTA/viennacl_ista.d 


# Each subdirectory must supply rules for building sources it contributes
Solvers/SubGradientDescent/ISTA/%.o: ../Solvers/SubGradientDescent/ISTA/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DNDEBUG -DW_OPENCL -DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN -I/usr/include/eigen3 -I/usr/include/viennacl -I/usr/local/cuda/include -O3 -mtune=native -march=native -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


