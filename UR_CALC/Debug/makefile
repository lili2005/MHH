################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SOURCE/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
UR_CALC.lss \

FLASH_IMAGE += \
UR_CALC.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: UR_CALC.elf secondary-outputs

# Tool invocations
UR_CALC.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,UR_CALC.map -mmcu=atmega32 -o "UR_CALC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

UR_CALC.lss: UR_CALC.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S UR_CALC.elf  >"UR_CALC.lss"
	@echo 'Finished building: $@'
	@echo ' '

UR_CALC.hex: UR_CALC.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex UR_CALC.elf  "UR_CALC.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: UR_CALC.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 UR_CALC.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) UR_CALC.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
