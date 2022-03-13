# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu
# BOOTLOADER = tinyuf2
# ENCODER_ENABLE = yes
# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix.c

EEPROM_DRIVER = custom
SRC += eep/eeprom_stm32.c
SRC += eep/flash_stm32.c
OPT_DEFS += -DEEPROM_EMU_STM32F401xC
