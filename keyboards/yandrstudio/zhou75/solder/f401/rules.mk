# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix.c


ENCODER_ENABLE = yes


# EEPROM_DRIVER = spi
EEPROM_DRIVER = custom
SRC += eep/eeprom_stm32.c
SRC += eep/flash_stm32.c
OPT_DEFS += -DEEPROM_EMU_STM32F401xC

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
