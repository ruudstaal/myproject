################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include befc/task/subdir.mk
-include befc/svi/value/subdir.mk
-include befc/svi/atomic/subdir.mk
-include befc/svi/subdir.mk
-include befc/smi/client/subdir.mk
-include befc/smi/calls/svi/subdir.mk
-include befc/smi/calls/subdir.mk
-include befc/smi/subdir.mk
-include befc/module/subdir.mk
-include befc/mio/util/processImage/subdir.mk
-include befc/mio/util/subdir.mk
-include befc/mio/configuration/subdir.mk
-include befc/mio/common/base/subdir.mk
-include befc/mio/common/subdir.mk
-include befc/mio/cards/UFB/subdir.mk
-include befc/mio/cards/NET/subdir.mk
-include befc/mio/cards/FCT/subdir.mk
-include befc/mio/cards/DO/subdir.mk
-include befc/mio/cards/DIO/subdir.mk
-include befc/mio/cards/DI/subdir.mk
-include befc/mio/cards/AO/subdir.mk
-include befc/mio/cards/AIO/subdir.mk
-include befc/mio/cards/AI/subdir.mk
-include befc/common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
COMPOUND_OBJ += \
project_all.o \

CCOMPOUND_OBJ += \
project.cco \

MODULE_OBJ += \
project.o \

MODULE_DBO += \
project.dbo \

SYMBOLS_LST += \
project.lst \

CTDT_C += \
ctdt.c \

AUXILIARY_OBJS += \
ctdt.o \


# All Target
all: project.m secondary-outputs

# Tool invocations
project.m: $(MODULE_OBJ) $(BCR_FILE)
	@echo 'Building target: $@'
	@echo 'Generating M-File'
	mbind project -c project.mbs -p "..\\"
	@echo 'Finished building target: $@'
	@echo ' '

project_all.o: $(OBJS) $(USER_OBJS)
	@echo 'Linking Project Objects'
	i386-wrs-vxworks-ld -r -d -nostdlib  -L"$(BAE_COMPILER_LIBS_PATH)" -L"$(BAE_COMPILER_VXWORKS_LIBS_PATH)" -o  "project_all.o" "makefile.lk" $(USER_OBJS) $(LIBS)
	@echo 'Finished building: $@'
	@echo ' '

project.cco: $(COMPOUND_OBJ)
	@echo 'Converting Symbols'
	symconv project -f project_all.o -o project.cco -i
	@echo 'Finished building: $@'
	@echo ' '

project.o: $(CCOMPOUND_OBJ) $(AUXILIARY_OBJS)
	@echo 'Generating Final Object File'
	i386-wrs-vxworks-ld -s -r -d -nostdlib  -L"$(BAE_COMPILER_LIBS_PATH)" -L"$(BAE_COMPILER_VXWORKS_LIBS_PATH)" -o  "project.o" $(CCOMPOUND_OBJ) $(AUXILIARY_OBJS)
	@echo 'Finished building: $@'
	@echo ' '

project.dbo: $(CCOMPOUND_OBJ) $(AUXILIARY_OBJS)
	@echo 'Generating DBO File'
	i386-wrs-vxworks-ld -r -d -nostdlib  -L"$(BAE_COMPILER_LIBS_PATH)" -L"$(BAE_COMPILER_VXWORKS_LIBS_PATH)" -o  "project.dbo" $(CCOMPOUND_OBJ) $(AUXILIARY_OBJS)
	@echo 'Finished building: $@'
	@echo ' '

project.lst: $(CCOMPOUND_OBJ)
	@echo 'Generating Symbols List From Object File'
	nm $(CCOMPOUND_OBJ) > "project.lst"
	@echo 'Finished building: $@'
	@echo ' '

ctdt.c: $(SYMBOLS_LST)
	@echo 'Generating Static Constructors/Destructors File'
	munch -gcc=4.1.2 $(SYMBOLS_LST) > ctdt.c
	@echo 'Finished building: $@'
	@echo ' '

ctdt.o: $(CTDT_C)
	@echo 'Compiling Static Constructors/Destructors'
	i386-wrs-vxworks-gcc  -c -g -fno-builtin -fno-defer-pop -nostdinc -march=pentium -xc -fno-common -DCPU_FAMILY=I80X86 -I"$(BAE_VXWORKS_INCLUDES_PATH)" -I"$(BAE_MSYS_INCLUDES_PATH)" -I"$(BAE_COMPILER_CONFIG_INCLUDES_PATH)" -I"$(BAE_VXWORKS_CORE_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_INCLUDES_PATH)" -I"$(BAE_COMPILER_CPP_VXWORKS_INCLUDES_PATH)" -Wno-pointer-sign -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/exception" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/AO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DI" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DIO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/DO" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/FCT" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/cards/NET" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/common/base" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/configuration" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/mio/util/processImage" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/module" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/client" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/smi/calls" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/svi/value" -I"C:/Users/rstaal/Documents/GitBachmann/Project/befc/task" -O0 -Wall -o "ctdt.o" $(CTDT_C)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(AUXILIARY_OBJS)$(MODULE_DBO)$(SYMBOLS_LST)$(C_BYACC)$(CCOMPOUND_OBJ)$(CTDT_C)$(BCR_FILE)$(MFILE)$(MODULE_OBJ)$(COMPOUND_OBJ)$(C_LEX)
	-@$(foreach DIR, $(SUBDIRS), $(shell $(RM) $(DIR)/*.o $(DIR)/*.d ))
	-$(RM)  project.m
	-@echo ' '

secondary-outputs: $(MODULE_OBJ) $(MODULE_DBO) $(BCR_FILE) $(CCOMPOUND_OBJ)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
