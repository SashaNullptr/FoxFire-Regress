################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Solvers/SubGradientDescent/FISTA/fista.cpp \
../Solvers/SubGradientDescent/FISTA/viennacl_fista.cpp 

OBJS += \
./Solvers/SubGradientDescent/FISTA/fista.o \
./Solvers/SubGradientDescent/FISTA/viennacl_fista.o 

CPP_DEPS += \
./Solvers/SubGradientDescent/FISTA/fista.d \
./Solvers/SubGradientDescent/FISTA/viennacl_fista.d 


# Each subdirectory must supply rules for building sources it contributes
Solvers/SubGradientDescent/FISTA/%.o: ../Solvers/SubGradientDescent/FISTA/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DNDEBUG -DW_OPENCL -DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN -I/usr/include/eigen3 -I/usr/include/viennacl -I/usr/local/cuda/include -O3 -mtune=native -march=native -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


