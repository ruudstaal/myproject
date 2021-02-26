################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/smi/calls/svi/ParametrizedObject.cpp \
../befc/smi/calls/svi/SviProcGetAddrCall.cpp \
../befc/smi/calls/svi/SviProcGetAddrReply.cpp \
../befc/smi/calls/svi/SviProcGetBlkCall.cpp \
../befc/smi/calls/svi/SviProcGetBlkReply.cpp \
../befc/smi/calls/svi/SviProcGetValCall.cpp \
../befc/smi/calls/svi/SviProcGetValLstCall.cpp \
../befc/smi/calls/svi/SviProcGetValLstReply.cpp \
../befc/smi/calls/svi/SviProcGetValReply.cpp \
../befc/smi/calls/svi/SviProcGetXAddrCall.cpp \
../befc/smi/calls/svi/SviProcGetXAddrReply.cpp \
../befc/smi/calls/svi/SviProcSetBlkCall.cpp \
../befc/smi/calls/svi/SviProcSetBlkReply.cpp \
../befc/smi/calls/svi/SviProcSetValCall.cpp \
../befc/smi/calls/svi/SviProcSetValLstCall.cpp \
../befc/smi/calls/svi/SviProcSetValLstReply.cpp \
../befc/smi/calls/svi/SviProcSetValReply.cpp 

OBJS += \
./befc/smi/calls/svi/ParametrizedObject.o \
./befc/smi/calls/svi/SviProcGetAddrCall.o \
./befc/smi/calls/svi/SviProcGetAddrReply.o \
./befc/smi/calls/svi/SviProcGetBlkCall.o \
./befc/smi/calls/svi/SviProcGetBlkReply.o \
./befc/smi/calls/svi/SviProcGetValCall.o \
./befc/smi/calls/svi/SviProcGetValLstCall.o \
./befc/smi/calls/svi/SviProcGetValLstReply.o \
./befc/smi/calls/svi/SviProcGetValReply.o \
./befc/smi/calls/svi/SviProcGetXAddrCall.o \
./befc/smi/calls/svi/SviProcGetXAddrReply.o \
./befc/smi/calls/svi/SviProcSetBlkCall.o \
./befc/smi/calls/svi/SviProcSetBlkReply.o \
./befc/smi/calls/svi/SviProcSetValCall.o \
./befc/smi/calls/svi/SviProcSetValLstCall.o \
./befc/smi/calls/svi/SviProcSetValLstReply.o \
./befc/smi/calls/svi/SviProcSetValReply.o 

CPP_DEPS += \
./befc/smi/calls/svi/ParametrizedObject.d \
./befc/smi/calls/svi/SviProcGetAddrCall.d \
./befc/smi/calls/svi/SviProcGetAddrReply.d \
./befc/smi/calls/svi/SviProcGetBlkCall.d \
./befc/smi/calls/svi/SviProcGetBlkReply.d \
./befc/smi/calls/svi/SviProcGetValCall.d \
./befc/smi/calls/svi/SviProcGetValLstCall.d \
./befc/smi/calls/svi/SviProcGetValLstReply.d \
./befc/smi/calls/svi/SviProcGetValReply.d \
./befc/smi/calls/svi/SviProcGetXAddrCall.d \
./befc/smi/calls/svi/SviProcGetXAddrReply.d \
./befc/smi/calls/svi/SviProcSetBlkCall.d \
./befc/smi/calls/svi/SviProcSetBlkReply.d \
./befc/smi/calls/svi/SviProcSetValCall.d \
./befc/smi/calls/svi/SviProcSetValLstCall.d \
./befc/smi/calls/svi/SviProcSetValLstReply.d \
./befc/smi/calls/svi/SviProcSetValReply.d 


# Each subdirectory must supply rules for building sources it contributes
befc/smi/calls/svi/%.o: ../befc/smi/calls/svi/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


