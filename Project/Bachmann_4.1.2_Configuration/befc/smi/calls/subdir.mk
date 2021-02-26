################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/smi/calls/Smi_ProcDeinit.cpp \
../befc/smi/calls/Smi_ProcEndOfInit.cpp \
../befc/smi/calls/Smi_ProcGetInfo.cpp \
../befc/smi/calls/Smi_ProcNewCfg.cpp \
../befc/smi/calls/Smi_ProcNull.cpp \
../befc/smi/calls/Smi_ProcReset.cpp \
../befc/smi/calls/Smi_ProcRun.cpp \
../befc/smi/calls/Smi_ProcSetDbg.cpp \
../befc/smi/calls/Smi_ProcStop.cpp \
../befc/smi/calls/Svi_Proc.cpp 

OBJS += \
./befc/smi/calls/Smi_ProcDeinit.o \
./befc/smi/calls/Smi_ProcEndOfInit.o \
./befc/smi/calls/Smi_ProcGetInfo.o \
./befc/smi/calls/Smi_ProcNewCfg.o \
./befc/smi/calls/Smi_ProcNull.o \
./befc/smi/calls/Smi_ProcReset.o \
./befc/smi/calls/Smi_ProcRun.o \
./befc/smi/calls/Smi_ProcSetDbg.o \
./befc/smi/calls/Smi_ProcStop.o \
./befc/smi/calls/Svi_Proc.o 

CPP_DEPS += \
./befc/smi/calls/Smi_ProcDeinit.d \
./befc/smi/calls/Smi_ProcEndOfInit.d \
./befc/smi/calls/Smi_ProcGetInfo.d \
./befc/smi/calls/Smi_ProcNewCfg.d \
./befc/smi/calls/Smi_ProcNull.d \
./befc/smi/calls/Smi_ProcReset.d \
./befc/smi/calls/Smi_ProcRun.d \
./befc/smi/calls/Smi_ProcSetDbg.d \
./befc/smi/calls/Smi_ProcStop.d \
./befc/smi/calls/Svi_Proc.d 


# Each subdirectory must supply rules for building sources it contributes
befc/smi/calls/%.o: ../befc/smi/calls/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


