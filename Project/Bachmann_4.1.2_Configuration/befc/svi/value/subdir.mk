################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/svi/value/ArrayValue.cpp \
../befc/svi/value/Bool8Value.cpp \
../befc/svi/value/Real32Value.cpp \
../befc/svi/value/Real64Value.cpp \
../befc/svi/value/Sint16Value.cpp \
../befc/svi/value/Sint32Value.cpp \
../befc/svi/value/Sint64Value.cpp \
../befc/svi/value/Sint8Value.cpp \
../befc/svi/value/StringValue.cpp \
../befc/svi/value/Uint16Value.cpp \
../befc/svi/value/Uint32Value.cpp \
../befc/svi/value/Uint64Value.cpp \
../befc/svi/value/Uint8Value.cpp \
../befc/svi/value/ValueFactory.cpp 

OBJS += \
./befc/svi/value/ArrayValue.o \
./befc/svi/value/Bool8Value.o \
./befc/svi/value/Real32Value.o \
./befc/svi/value/Real64Value.o \
./befc/svi/value/Sint16Value.o \
./befc/svi/value/Sint32Value.o \
./befc/svi/value/Sint64Value.o \
./befc/svi/value/Sint8Value.o \
./befc/svi/value/StringValue.o \
./befc/svi/value/Uint16Value.o \
./befc/svi/value/Uint32Value.o \
./befc/svi/value/Uint64Value.o \
./befc/svi/value/Uint8Value.o \
./befc/svi/value/ValueFactory.o 

CPP_DEPS += \
./befc/svi/value/ArrayValue.d \
./befc/svi/value/Bool8Value.d \
./befc/svi/value/Real32Value.d \
./befc/svi/value/Real64Value.d \
./befc/svi/value/Sint16Value.d \
./befc/svi/value/Sint32Value.d \
./befc/svi/value/Sint64Value.d \
./befc/svi/value/Sint8Value.d \
./befc/svi/value/StringValue.d \
./befc/svi/value/Uint16Value.d \
./befc/svi/value/Uint32Value.d \
./befc/svi/value/Uint64Value.d \
./befc/svi/value/Uint8Value.d \
./befc/svi/value/ValueFactory.d 


# Each subdirectory must supply rules for building sources it contributes
befc/svi/value/%.o: ../befc/svi/value/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


