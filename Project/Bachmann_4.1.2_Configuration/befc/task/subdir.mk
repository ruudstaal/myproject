################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/task/BETask.cpp \
../befc/task/BETaskConfiguration.cpp \
../befc/task/BETaskState.cpp \
../befc/task/InitializedState.cpp \
../befc/task/RunState.cpp \
../befc/task/SuspendedState.cpp 

OBJS += \
./befc/task/BETask.o \
./befc/task/BETaskConfiguration.o \
./befc/task/BETaskState.o \
./befc/task/InitializedState.o \
./befc/task/RunState.o \
./befc/task/SuspendedState.o 

CPP_DEPS += \
./befc/task/BETask.d \
./befc/task/BETaskConfiguration.d \
./befc/task/BETaskState.d \
./befc/task/InitializedState.d \
./befc/task/RunState.d \
./befc/task/SuspendedState.d 


# Each subdirectory must supply rules for building sources it contributes
befc/task/%.o: ../befc/task/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


