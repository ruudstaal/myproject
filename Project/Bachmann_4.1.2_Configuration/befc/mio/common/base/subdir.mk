################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/mio/common/base/AnalogChannel.cpp \
../befc/mio/common/base/BasicAnalogModule.cpp \
../befc/mio/common/base/BasicChannel.cpp \
../befc/mio/common/base/BasicDigitalModule.cpp \
../befc/mio/common/base/BasicIoModule.cpp \
../befc/mio/common/base/BasicMixedModule.cpp \
../befc/mio/common/base/DigitalChannel.cpp \
../befc/mio/common/base/MIOerrorcode.cpp \
../befc/mio/common/base/MIOexception.cpp 

OBJS += \
./befc/mio/common/base/AnalogChannel.o \
./befc/mio/common/base/BasicAnalogModule.o \
./befc/mio/common/base/BasicChannel.o \
./befc/mio/common/base/BasicDigitalModule.o \
./befc/mio/common/base/BasicIoModule.o \
./befc/mio/common/base/BasicMixedModule.o \
./befc/mio/common/base/DigitalChannel.o \
./befc/mio/common/base/MIOerrorcode.o \
./befc/mio/common/base/MIOexception.o 

CPP_DEPS += \
./befc/mio/common/base/AnalogChannel.d \
./befc/mio/common/base/BasicAnalogModule.d \
./befc/mio/common/base/BasicChannel.d \
./befc/mio/common/base/BasicDigitalModule.d \
./befc/mio/common/base/BasicIoModule.d \
./befc/mio/common/base/BasicMixedModule.d \
./befc/mio/common/base/DigitalChannel.d \
./befc/mio/common/base/MIOerrorcode.d \
./befc/mio/common/base/MIOexception.d 


# Each subdirectory must supply rules for building sources it contributes
befc/mio/common/base/%.o: ../befc/mio/common/base/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


