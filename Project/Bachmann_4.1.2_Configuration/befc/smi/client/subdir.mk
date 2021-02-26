################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/smi/client/BaseSMIClient.cpp \
../befc/smi/client/GetModuleInfoCall.cpp \
../befc/smi/client/GetModuleInfoReply.cpp \
../befc/smi/client/LocalSmiClient.cpp \
../befc/smi/client/RemoteSmiClient.cpp \
../befc/smi/client/ResProcLoginCall.cpp \
../befc/smi/client/ResProcLoginReply.cpp \
../befc/smi/client/ResProcLogoutCall.cpp \
../befc/smi/client/ResProcLogoutReply.cpp \
../befc/smi/client/ResProcModNBCall.cpp \
../befc/smi/client/ResProcModNBReply.cpp \
../befc/smi/client/ResProcSysInfoCall.cpp \
../befc/smi/client/ResProcSysInfoReply.cpp \
../befc/smi/client/SmiCall.cpp 

OBJS += \
./befc/smi/client/BaseSMIClient.o \
./befc/smi/client/GetModuleInfoCall.o \
./befc/smi/client/GetModuleInfoReply.o \
./befc/smi/client/LocalSmiClient.o \
./befc/smi/client/RemoteSmiClient.o \
./befc/smi/client/ResProcLoginCall.o \
./befc/smi/client/ResProcLoginReply.o \
./befc/smi/client/ResProcLogoutCall.o \
./befc/smi/client/ResProcLogoutReply.o \
./befc/smi/client/ResProcModNBCall.o \
./befc/smi/client/ResProcModNBReply.o \
./befc/smi/client/ResProcSysInfoCall.o \
./befc/smi/client/ResProcSysInfoReply.o \
./befc/smi/client/SmiCall.o 

CPP_DEPS += \
./befc/smi/client/BaseSMIClient.d \
./befc/smi/client/GetModuleInfoCall.d \
./befc/smi/client/GetModuleInfoReply.d \
./befc/smi/client/LocalSmiClient.d \
./befc/smi/client/RemoteSmiClient.d \
./befc/smi/client/ResProcLoginCall.d \
./befc/smi/client/ResProcLoginReply.d \
./befc/smi/client/ResProcLogoutCall.d \
./befc/smi/client/ResProcLogoutReply.d \
./befc/smi/client/ResProcModNBCall.d \
./befc/smi/client/ResProcModNBReply.d \
./befc/smi/client/ResProcSysInfoCall.d \
./befc/smi/client/ResProcSysInfoReply.d \
./befc/smi/client/SmiCall.d 


# Each subdirectory must supply rules for building sources it contributes
befc/smi/client/%.o: ../befc/smi/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


