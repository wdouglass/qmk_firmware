# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = stm32duino

MCU_LDSCRIPT = STM32F103xB_uf2
BOARD = STM32_F103_STM32DUINO
BOOTLOADER = tinyuf2
FIRMWARE_FORMAT = uf2
MCU_STARTUP ?= stm32f1xx

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
# WS2812_DRIVER = pwm

CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix_io.c 74hc595_io.c

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -p FFFF -v FFFF
# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
