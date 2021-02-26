################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../befc/svi/AbstractSviGroup.cpp \
../befc/svi/AbstractSviItem.cpp \
../befc/svi/ListReadStrategyImpl.cpp \
../befc/svi/LocalSviItem.cpp \
../befc/svi/M1SviSystem.cpp \
../befc/svi/RemoteSviGroup.cpp \
../befc/svi/RemoteSviItem.cpp \
../befc/svi/RemoteSviListReadStrategy.cpp \
../befc/svi/RemoteSviReadStrategy.cpp \
../befc/svi/RemoteSviWriteHelper.cpp \
../befc/svi/SingleItemReadStrategyImpl.cpp \
../befc/svi/SviExportDescriptor.cpp \
../befc/svi/SviExportHelper.cpp \
../befc/svi/SviGroup.cpp \
../befc/svi/SviItemModulewrapper.cpp \
../befc/svi/SviServer.cpp \
../befc/svi/SviValueExportDescriptor.cpp \
../befc/svi/SviVirtualExportDescriptor.cpp 

OBJS += \
./befc/svi/AbstractSviGroup.o \
./befc/svi/AbstractSviItem.o \
./befc/svi/ListReadStrategyImpl.o \
./befc/svi/LocalSviItem.o \
./befc/svi/M1SviSystem.o \
./befc/svi/RemoteSviGroup.o \
./befc/svi/RemoteSviItem.o \
./befc/svi/RemoteSviListReadStrategy.o \
./befc/svi/RemoteSviReadStrategy.o \
./befc/svi/RemoteSviWriteHelper.o \
./befc/svi/SingleItemReadStrategyImpl.o \
./befc/svi/SviExportDescriptor.o \
./befc/svi/SviExportHelper.o \
./befc/svi/SviGroup.o \
./befc/svi/SviItemModulewrapper.o \
./befc/svi/SviServer.o \
./befc/svi/SviValueExportDescriptor.o \
./befc/svi/SviVirtualExportDescriptor.o 

CPP_DEPS += \
./befc/svi/AbstractSviGroup.d \
./befc/svi/AbstractSviItem.d \
./befc/svi/ListReadStrategyImpl.d \
./befc/svi/LocalSviItem.d \
./befc/svi/M1SviSystem.d \
./befc/svi/RemoteSviGroup.d \
./befc/svi/RemoteSviItem.d \
./befc/svi/RemoteSviListReadStrategy.d \
./befc/svi/RemoteSviReadStrategy.d \
./befc/svi/RemoteSviWriteHelper.d \
./befc/svi/SingleItemReadStrategyImpl.d \
./befc/svi/SviExportDescriptor.d \
./befc/svi/SviExportHelper.d \
./befc/svi/SviGroup.d \
./befc/svi/SviItemModulewrapper.d \
./befc/svi/SviServer.d \
./befc/svi/SviValueExportDescriptor.d \
./befc/svi/SviVirtualExportDescriptor.d 


# Each subdirectory must supply rules for building sources it contributes
befc/svi/%.o: ../befc/svi/%.cpp
	@echo 'Building file: $<'
	@echo 'Compiling Project Sources'
	i386-wrs-vxworks-g++  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc++ -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -MD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


