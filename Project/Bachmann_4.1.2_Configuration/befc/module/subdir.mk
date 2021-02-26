################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/module/BEModule.cpp \
../befc/module/BEModuleState.cpp \
../befc/module/CfgState.cpp \
../befc/module/DeInitState.cpp \
../befc/module/EOIState.cpp \
../befc/module/ErrorState.cpp \
../befc/module/InitState.cpp \
../befc/module/ModuleConfiguration.cpp \
../befc/module/ResetState.cpp \
../befc/module/RunState.cpp \
../befc/module/StopState.cpp 

OBJS += \
./befc/module/BEModule.o \
./befc/module/BEModuleState.o \
./befc/module/CfgState.o \
./befc/module/DeInitState.o \
./befc/module/EOIState.o \
./befc/module/ErrorState.o \
./befc/module/InitState.o \
./befc/module/ModuleConfiguration.o \
./befc/module/ResetState.o \
./befc/module/RunState.o \
./befc/module/StopState.o 

CPP_DEPS += \
./befc/module/BEModule.d \
./befc/module/BEModuleState.d \
./befc/module/CfgState.d \
./befc/module/DeInitState.d \
./befc/module/EOIState.d \
./befc/module/ErrorState.d \
./befc/module/InitState.d \
./befc/module/ModuleConfiguration.d \
./befc/module/ResetState.d \
./befc/module/RunState.d \
./befc/module/StopState.d 


# Each subdirectory must supply rules for building sources it contributes
befc/module/%.o: ../befc/module/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


