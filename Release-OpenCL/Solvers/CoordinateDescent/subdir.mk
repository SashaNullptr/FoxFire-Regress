################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Solvers/CoordinateDescent/coordinate_descent.cpp \
../Solvers/CoordinateDescent/coordinatedescentwithscreen.cpp 

OBJS += \
./Solvers/CoordinateDescent/coordinate_descent.o \
./Solvers/CoordinateDescent/coordinatedescentwithscreen.o 

CPP_DEPS += \
./Solvers/CoordinateDescent/coordinate_descent.d \
./Solvers/CoordinateDescent/coordinatedescentwithscreen.d 


# Each subdirectory must supply rules for building sources it contributes
Solvers/CoordinateDescent/%.o: ../Solvers/CoordinateDescent/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DNDEBUG -DW_OPENCL -DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN -I/usr/include/eigen3 -I/usr/include/viennacl -I/usr/local/cuda/include -O3 -mtune=native -march=native -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


