# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2023-09-05 - Add dir_guard, remove unnecessary comments and flags
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = Temperature-Logger
#TARGET = grp-11-micro-minions


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES = \
stm32_startup.c\
src/main.c \
src/button.c \
src/led.c \
src/lcd.c \
src/pacer.c \
src/usart.c \
src/mySPI1.c \
src/mySPI2.c \
src/lcd_driver.c \
src/system_stm32f4xx.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c 

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
DEFAULT_GCC_PATH=/usr/bin
CC = $(DEFAULT_GCC_PATH)/$(PREFIX)gcc
AS = $(DEFAULT_GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(DEFAULT_GCC_PATH)/$(PREFIX)objcopy
SZ = $(DEFAULT_GCC_PATH)/$(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DHSE_VALUE=8000000 \
-DHSE_STARTUP_TIMEOUT=100 \
-DLSE_STARTUP_TIMEOUT=5000 \
-DLSE_VALUE=32768 \
-DEXTERNAL_CLOCK_VALUE=12288000 \
-DHSI_VALUE=16000000 \
-DLSI_VALUE=32000 \
-DVDD_VALUE=3300 \
-DPREFETCH_ENABLE=1 \
-DINSTRUCTION_CACHE_ENABLE=1 \
-DDATA_CACHE_ENABLE=1 \
-DSTM32F446xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-Iinc \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

dir_guard = @mkdir -p $(@D)

.phony: clean flash reset erase help

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c 
	$(dir_guard)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s 
	$(dir_guard)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf 
	$(dir_guard)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(dir_guard)
	$(BIN) $< $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(dir_guard)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

############################################
# clean up
############################################
clean:
	- @rm -rf $(BUILD_DIR)
	@echo "Removed build directory: $(BUILD_DIR)"

############################################
# STM32 flash, base address: 0x08000000
############################################
flash: $(BUILD_DIR)/$(TARGET).bin
	st-flash --reset --connect-under-reset write $(BUILD_DIR)/$(TARGET).bin 0x8000000 

############################################
# STM32 reset
############################################
reset:
	st-flash --connect-under-reset reset

############################################
# STM32 erase (delete current program on MCU)
############################################
erase:
	st-flash --connect-under-reset erase

############################################
# Help to explain the targets
############################################
help:
	@echo "STM32 F446 template"
	@echo "Usage: make <target>"
	@echo "Short description about the stm32 template to build with the Makefile:"
	@echo "\t all \t Build all - see the C_SOURCES for compiled source files"
	@echo "\t clean \t Clean up the build directory"
	@echo "\t flash \t Flash the MCU"
	@echo "\t reset \t Reset the MCU"
	@echo "\t erase \t Erase the mass of the device storage"
	@echo "\t help \t Print this help"
	@echo ""
	@echo "For more information, read the README"

-include $(wildcard $(BUILD_DIR)/*.d)
