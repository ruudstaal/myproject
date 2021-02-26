################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/mio/cards/DO/DO216.cpp \
../befc/mio/cards/DO/DO232.cpp \
../befc/mio/cards/DO/DOR206.cpp 

OBJS += \
./befc/mio/cards/DO/DO216.o \
./befc/mio/cards/DO/DO232.o \
./befc/mio/cards/DO/DOR206.o 

CPP_DEPS += \
./befc/mio/cards/DO/DO216.d \
./befc/mio/cards/DO/DO232.d \
./befc/mio/cards/DO/DOR206.d 


# Each subdirectory must supply rules for building sources it contributes
befc/mio/cards/DO/%.o: ../befc/mio/cards/DO/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


