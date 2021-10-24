<<<<<<< HEAD
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pruebaBT.axf

# Tool invocations
pruebaBT.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\matia\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map="pruebaBT.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "pruebaBT_Debug.ld" -o "pruebaBT.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) pruebaBT.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "pruebaBT.axf"; # arm-none-eabi-objcopy -v -O binary "pruebaBT.axf" "pruebaBT.bin" ; # checksum -p LPC1769 -d "pruebaBT.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
=======
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pruebaBT.axf

# Tool invocations
pruebaBT.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\matia\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map="pruebaBT.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "pruebaBT_Debug.ld" -o "pruebaBT.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) pruebaBT.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "pruebaBT.axf"; # arm-none-eabi-objcopy -v -O binary "pruebaBT.axf" "pruebaBT.bin" ; # checksum -p LPC1769 -d "pruebaBT.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
>>>>>>> 0452199 (Correccion de error en recepcion y agregado de transmision)
